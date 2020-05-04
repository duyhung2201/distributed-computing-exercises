# WordCount
export PATH=${JAVA_HOME}/bin:${PATH}               
export HADOOP_CLASSPATH=${JAVA_HOME}/lib/tools.jar
bin/hadoop com.sun.tools.javac.Main WordCount.java
$ jar cf wc.jar WordCount*.class
hadoop fs -get /user/Hadoop/wordcount/output 
sort -k 2nr output/part-r-00000 | head  -n 10