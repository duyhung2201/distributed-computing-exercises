



contents = []
X_train = []
y_train = []
f = open("data/train_neg.txt", "r")
data = f.read()
lines = data.split("\n")
for line in lines:
    if( line != ' '):
        X_train.append(line)
        contents.append(line)
        y_train.append(0)
f.close()

del X_train[-1]
del y_train[-1]
del contents[-1]

f = open("data/train_pos.txt", "r")
data = f.read()
lines = data.split("\n")
for line in lines:
    if( line != ' ' and line != '\n'):
        X_train.append(line)
        contents.append(line)
        y_train.append(1)
f.close()
del X_train[-1]
del y_train[-1]
del contents[-1]



#X_val = []
#y_val = []
f = open("data/val_neg.txt", "r")
data = f.read()
lines = data.split("\n")
for line in lines:
    if( line != ' ' ):
        X_train.append(line)
        contents.append(line)
        y_train.append(0)
f.close()
del X_train[-1]
del y_train[-1]
del contents[-1]

f = open("data/val_pos.txt", "r")
data = f.read()
lines = data.split("\n")
for line in lines:
    if( line != ' ' and line != '\n'):
        X_train.append(line)
        contents.append(line)
        y_train.append(1)

f.close()
del X_train[-1]
del y_train[-1]
del contents[-1]

print(len(X_train))
print(len(y_train))


X_test = []
y_test = []
f = open("data/test_neg.txt", "r")
data = f.read()
lines = data.split("\n")
for line in lines:
    if( line != ' ' and line != '\n'):
        X_test.append(line)
        contents.append(line)
        y_test.append(0)
f.close()

del X_test[-1]
del y_test[-1]
del contents[-1]

f = open("data/test_pos.txt", "r")
data = f.read()
lines = data.split("\n")
for line in lines:
    if( line != ' ' and line != '\n'):
        X_test.append(line)
        contents.append(line)
        y_test.append(1)
f.close()

del X_test[-1]
del y_test[-1]
del contents[-1]
print(len(X_test))
print(len(y_test))



import numpy as np 
from sklearn.feature_extraction.text import CountVectorizer, TfidfVectorizer
from scipy import sparse, io

from sklearn import svm
from sklearn import metrics
from scipy import io


vectorizer = CountVectorizer()

tfidf_vectorizer = TfidfVectorizer(min_df = 0.0005, max_df = 0.990)
X = tfidf_vectorizer.fit_transform(contents)
vocab =  tfidf_vectorizer.get_feature_names()

print(len(vocab))

X_train = X[0: 40000, :]

X_test = X[40000: , :]


clf = svm.SVC(kernel='linear')

clf.fit(X_train, y_train)

y_pred = clf.predict(X_test.toarray())
# Model accuracy: how often is the classifier correct?
print("Accuracy: ", 100*metrics.accuracy_score(y_test, y_pred))

print("Precision: ", 100*metrics.precision_score(y_test, y_pred))

print("Recall (macro): ", 100*metrics.recall_score(y_test, y_pred, average='macro'))


print("Recall(micro): ", 100*metrics.recall_score(y_test, y_pred, average='micro'))

print("F1-scores(macro): ", 100*metrics.f1_score(y_test, y_pred, average='macro'))

print("F1-scores(micro): ", 100*metrics.f1_score(y_test, y_pred, average='micro'))

