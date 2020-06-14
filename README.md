Sentiment Analysis with PySpark

cd TwitterStreaming


python TwitterHttpClient/twitter_app.py

open another shell
<!-- spark-submit TwitterHttpClient/spark_app.py -->
spark-submit --master "local[4]" TwitterHttpClient/spark_app.py

open another shell 
python HashtagsDashboard/app.py 

open web-browser
http://localhost:5001