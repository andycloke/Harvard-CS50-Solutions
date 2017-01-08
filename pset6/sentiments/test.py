import nltk

class Analyzer():
    """Implements sentiment analysis."""

    def __init__(self, positives, negatives):
        """Initialize Analyzer."""
        self.positives = list()
        self.negatives = list()
        # populate positive word list (assuming one word per line, so no need to call split())
        p = open(positives)
        for line in p:
            if not line.startswith(';'):
                self.positives.append(line.strip())
        p.close()
        # populate negative word list
        n = open(negatives)
        for line in n:
            if not line.startswith(';'):
                self.negatives.append(line.strip())
        n.close()

    def analyze(self, text):
        """Analyze text for sentiment, returning its score."""
        counter = 0

        # create list of words in input text
        words = text.split()

        # for each input word
        for word in words:

            # add 1 to counter if word is in positive word list
            for posword in self.positives:
                if word == posword:
                    counter += 1

            # subtract -1 from counter if word is in negative word list
            for negword in self.negatives:
                if word == negword:
                    counter -= 1
        return counter

analyzer = Analyzer('positive-words.txt', 'negative-words.txt')
testword = 'I love you'
score = analyzer.analyze(testword)
print(testword + ': ' + str(score))
