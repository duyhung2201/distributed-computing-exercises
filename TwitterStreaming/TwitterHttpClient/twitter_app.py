import socket
import sys
import requests
import requests_oauthlib
import json
from vaderSentiment.vaderSentiment import SentimentIntensityAnalyzer

# Replace the values below with yours
ACCESS_TOKEN = "2455225267-TUcTHNheAWqWVBuaE72v5yB6mzdHuw7fJZfyglJ"
ACCESS_SECRET = "8MCbVbzFH2tn50Gkb1VLWMStJGYdcyHvFMM6WqGVbCds8"
CONSUMER_KEY = 'eLWxJbi9lHqDfZmmHsUY5mz8z'
CONSUMER_SECRET = 'QAnQ63QdgGNX2h7w82s0qqejFmpdXjYbUblOREZzy5WmHFPrsR'
my_auth = requests_oauthlib.OAuth1(CONSUMER_KEY, CONSUMER_SECRET,ACCESS_TOKEN, ACCESS_SECRET)

analyzer = SentimentIntensityAnalyzer()

def send_tweets_to_spark(http_resp, tcp_connection):
    for line in http_resp.iter_lines():
        try:
            full_tweet = json.loads(line)
            tweet_text = str(full_tweet['text'].encode("utf-8")).lower()
            sentiment_score = analyzer.polarity_scores(tweet_text)["compound"]
            if sentiment_score >= 0.05:
                sentiment = "POSITIVE"
            elif sentiment_score <= -0.05:
                sentiment = "NEGATIVE"
            else:
                sentiment = "NEUTRAL"
            mess =  sentiment + '||||' + tweet_text + '\n' 
            tcp_connection.send(bytes(mess, 'utf-8'))
        except:
            e = sys.exc_info()[0]
            print("Error: %s" % e)


def get_tweets():
    url = 'https://stream.twitter.com/1.1/statuses/filter.json'
    # query_data = [('language', 'en'), ('locations', '105.529736,20.746974,106.055520,21.151965')]
    # query_data = [('language', 'en'), ('locations', '-122.75,36.8,-121.75,37.8,-74,40,-73,41')] #this location value is San Francisco & NYC
    query_data = [('language', 'en'), ('follow', '25073877')]
    query_url = url + '?' + '&'.join([str(t[0]) + '=' + str(t[1]) for t in query_data])
    response = requests.get(query_url, auth=my_auth, stream=True)
    print(query_url, response)
    return response


TCP_IP = "localhost"
TCP_PORT = 9009
conn = None
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((TCP_IP, TCP_PORT))
s.listen(1)
print("Waiting for TCP connection...")
conn, addr = s.accept()
print("Connected... Starting getting tweets.")
resp = get_tweets()
send_tweets_to_spark(resp,conn)



