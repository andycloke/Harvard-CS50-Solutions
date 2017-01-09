from cs50 import SQL
import datetime
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from passlib.apps import custom_app_context as pwd_context
from tempfile import gettempdir

from helpers import *

# configure application
app = Flask(__name__)

# ensure responses aren't cached
if app.config["DEBUG"]:
    @app.after_request
    def after_request(response):
        response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
        response.headers["Expires"] = 0
        response.headers["Pragma"] = "no-cache"
        return response

# custom filter
app.jinja_env.filters["usd"] = usd

# configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = gettempdir()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

@app.route("/")
@login_required
def index():

    # get id as it is used several times
    id = session["user_id"]

    # get list of shares owned by user
    owned = db.execute("SELECT symbol, shares FROM portfolio WHERE id = :id", id=id)

    # initialise array to be passed to template
    stocks = []

    # counter
    i = 0

    # initalise total share value
    share_value = 0;

    # iterate over shares owned
    for share in owned:

        # temp dict
        dic = {}

        # store stock symbol
        dic['symbol'] = share['symbol']

        # lookup price on yahoo
        price = lookup(share['symbol'])

        # set dict price to current price
        dic['price'] = usd(price['price'])

        # set dict volume to volume owned
        dic['num_shares'] = share['shares']

        # value of current shares
        val = share['shares'] * price['price']

        # set dict value
        dic['value'] = usd(val)

        # sum total share value
        share_value += val

        # add dict to stocks array
        stocks.append(dic)

        # iterate
        i += 1

    # current cash
    cash_balance = db.execute("SELECT cash FROM users WHERE id = :id", id=id)
    cash_balance = cash_balance[0]['cash']

    # pass data to template
    return render_template("index.html", stocks = stocks, share_value = usd(share_value), cash_balance = usd(cash_balance), total_value = usd(share_value + cash_balance))

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock."""

     # if user reached route via GET return them an input form
    if request.method == "GET":
        return render_template("buy.html")

    # if user reached route via POST (as by submitting a form via POST)
    elif request.method == "POST":

        # get id as it is used many times
        id = session["user_id"]

        # get symbol as it is used many times
        symbol = request.form.get("symbol")

         # get share volume requested
        volume = int(request.form.get("volume"))

        # ensure stock symbol was submitted
        if not symbol:
            return apology("you must provide a stock symbol")

        # ensure positive volume (integer rule handled elsewhere)
        elif volume <= 0:
            return apology("volume must be integer greater than 0")

        # lookup stock on yahoo
        stock_info = lookup(symbol)

        # if error looking stock up
        if not stock_info:
            return apology("that stock symbol doesn't exist")

        # query database for cash balance
        cash = db.execute("SELECT cash FROM users WHERE id = :id", id=id)
        cash = cash[0]['cash']

        # cost of requested shares
        purchase_cost = volume * stock_info['price']

        # if sufficient cash, make purchase, else return apology
        if purchase_cost <= cash:

            # check if user already owns any stock in this company
            existing = db.execute("SELECT shares FROM portfolio WHERE id = :id AND symbol = :symbol", id=id, symbol=symbol)

            # if no existing shares, add them
            if not existing:
                new = db.execute("INSERT INTO portfolio (id, symbol, shares) VALUES(:id, :symbol, :shares)", id=id, symbol=symbol, shares=volume)

            # if there are existing shares, add new volume to them
            else:
                add = db.execute("UPDATE portfolio SET shares = :shares WHERE id = :id AND symbol = :symbol", shares=existing[0]['shares'] + volume, id=id, symbol=symbol)

            # set date string
            dstring = str(datetime.datetime.utcnow())

            # update transaction history
            result2 = db.execute("INSERT INTO `transaction` (id, symbol, volume, share_price, dtstamp) VALUES(:id, :symbol, :volume, :share_price, :dtstamp)", id=id, symbol=symbol, volume=volume, share_price=stock_info['price'], dtstamp=dstring)

            # reduce cash balance
            result = db.execute("UPDATE users SET cash = :cash WHERE id = :id", cash=cash-purchase_cost, id=id)

            return apology("TODO: index")
        else:
            return apology("insufficient funds")


@app.route("/history")
@login_required
def history():
    """Show history of transactions."""
    return apology("TODO")

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in."""

    # forget any user_id
    session.clear()

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

        # ensure username exists and password is correct
        if len(rows) != 1 or not pwd_context.verify(request.form.get("password"), rows[0]["hash"]):
            return apology("invalid username and/or password")

        # remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # redirect user to home page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")

@app.route("/logout")
def logout():
    """Log user out."""

    # forget any user_id
    session.clear()

    # redirect user to login form
    return redirect(url_for("login"))

@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # if user reached route via GET return them an input form
    if request.method == "GET":
        return render_template("quote.html")

    # if user reached route via POST (as by submitting a form via POST)
    elif request.method == "POST":

        # ensure stock symbol was submitted
        if not request.form.get("symbol"):
            return apology("you must provide a stock symbol")

        # lookup stock on yahoo
        stock_info = lookup(request.form.get("symbol"))

        # if error looking stock up
        if not stock_info:
            return apology("that stock symbol doesn't exist")

        # output stock info
        else:
            return render_template("quoted.html", name = stock_info['name'], price = stock_info['price'], symbol = stock_info['symbol'])


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user."""
    # forget any user_id
    session.clear()

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # ensure second password was submitted
        elif not request.form.get("retypepassword"):
            return apology("must retype password")

        # ensure passwords match
        elif request.form.get("password") != request.form.get("retypepassword"):
            return apology("passwords must match")

        # add user to database
        result = db.execute("INSERT INTO users (username, hash) VALUES(:username, :hash)", username=request.form.get("username"), hash=pwd_context.hash(request.form.get("password")))

        # check if username already exists
        if not result:
            return apology("that username is taken, please select another")

        # automatically log user in after registration
        session["user_id"] = result

       # redirect user to home page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock."""
    return apology("TODO")
