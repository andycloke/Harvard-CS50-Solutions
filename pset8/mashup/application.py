import os
import re
from flask import Flask, g, jsonify, render_template, request, url_for
from flask_jsglue import JSGlue

import sqlite3
from helpers import lookup

# configure application
app = Flask(__name__)
JSGlue(app)

# ensure responses aren't cached
if app.config["DEBUG"]:
    @app.after_request
    def after_request(response):
        response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
        response.headers["Expires"] = 0
        response.headers["Pragma"] = "no-cache"
        return response

# configure database connection
DATABASE = 'mashup.db'

def get_db():
    """ create connection to db """
    db = getattr(g, '_database', None)
    if db is None:
        db = g._database = sqlite3.connect(DATABASE)
    db.row_factory = sqlite3.Row
    return db

@app.teardown_appcontext
def close_connection(exception):
    """ close connection to database """
    db = getattr(g, '_database', None)
    if db is not None:
        db.close()

def query_db(query, args=(), one=False):
    """ Query Database """
    # http://stackoverflow.com/a/3287775/7216122
    cur = get_db().execute(query, args)
    r = [dict((cur.description[i][0], value) \
               for i, value in enumerate(row)) for row in cur.fetchall()]
    cur.connection.close()
    return (r[0] if r else None) if one else r


@app.route("/")
def index():
    """Render map."""
    if not os.environ.get("API_KEY"):
        raise RuntimeError("API_KEY not set")
    return render_template("index.html", key=os.environ.get("API_KEY"))

@app.route("/articles")
def articles():
    """Look up articles for geo."""

    # ensure parameter is present
    if not request.args.get("geo"):
        raise RuntimeError("missing get")

    # lookup news on google, return in JSON format
    return jsonify(lookup(request.args.get("geo")))

@app.route("/search")
def search():
    """Search for places that match query."""

    # ensure parameter is present
    if not request.args.get("q"):
        raise RuntimeError("missing q")

    q = request.args.get("q") + "%"

    rows = query_db("""SELECT * FROM places WHERE postal_code LIKE ? OR place_name LIKE ? OR admin_name1 LIKE ?""", [q, q, q])

    return jsonify(rows)

@app.route("/update")
def update():
    """Find up to 10 places within view."""

    # ensure parameters are present
    if not request.args.get("sw"):
        raise RuntimeError("missing sw")
    if not request.args.get("ne"):
        raise RuntimeError("missing ne")

    # ensure parameters are in lat,lng format
    if not re.search("^-?\d+(?:\.\d+)?,-?\d+(?:\.\d+)?$", request.args.get("sw")):
        raise RuntimeError("invalid sw")
    if not re.search("^-?\d+(?:\.\d+)?,-?\d+(?:\.\d+)?$", request.args.get("ne")):
        raise RuntimeError("invalid ne")

    # explode southwest corner into two variables
    (sw_lat, sw_lng) = [float(s) for s in request.args.get("sw").split(",")]

    # explode northeast corner into two variables
    (ne_lat, ne_lng) = [float(s) for s in request.args.get("ne").split(",")]

    # find 10 cities within view, pseudorandomly chosen if more within view
    if (sw_lng <= ne_lng):

        # doesn't cross the antimeridian
        rows = query_db("""SELECT * FROM places
            WHERE ? <= latitude AND latitude <= ? AND (? <= longitude AND longitude <= ?)
            GROUP BY country_code, place_name, admin_code1
            ORDER BY RANDOM()
            LIMIT 10""",
            [sw_lat, ne_lat, sw_lng, ne_lng])

    else:

        # crosses the antimeridian
        rows = query_db("""SELECT * FROM places
            WHERE ? <= latitude AND latitude <= ? AND (? <= longitude OR longitude <= ?)
            GROUP BY country_code, place_name, admin_code1
            ORDER BY RANDOM()
            LIMIT 10""",
            [sw_lat, ne_lat, sw_lng, ne_lng])

    # output places as JSON
    return jsonify(rows)
