from sklearn import svm
import sys
import random

#initializing
train   = []
answer  = []
testing = []

#reading input and parsing
for line in open('train.csv', 'r'):
    temp = list(map(float, line.split(',')))
    train.append(temp[:-1])
    answer.append(temp[-1])
for line in open('test.csv', 'r'):
    testing.append(list(map(float, line.split(','))))

#checking how efficiently works one method. return percent of correct answers
def training(train, test, answerTrain, answerTest):
    print(clf)
    clf.fit(train, answerTrain)
    correct = 0
    x       = clf.predict(test)
    n       = len(test)
    for i in range(n):
        if answerTest[i] == x[i]:
            correct += 1
    return correct / n

#unless we had test with answers, do it
#dividing training set on 5 partitions : 4 fisrt -- training, 5th -- test
n           = len(train)
k           = n // 5
test        = train[-k:]
train       = train[:-k]
answerTest  = answer[-k:]
answerTrain = answer[:-k]

#try different kernels and parametres, choose with max percent
clf = svm.SVC()
print(training(train, test, answerTrain, answerTest))

clf = svm.SVC(kernel='linear')
print(training(train, test, answerTrain, answerTest))

clf = svm.SVC(kernel='sigmoid')
print(training(train, test, answerTrain, answerTest))

clf = svm.SVC(kernel='sigmoid', gamma=2)
print(training(train, test, answerTrain, answerTest))

clf = svm.SVC(kernel='sigmoid', gamma=2, coef0=2)
print(training(train, test, answerTrain, answerTest))

clf = svm.SVC(kernel='poly')
print(training(train, test, answerTrain, answerTest))

clf = svm.SVC(kernel='poly',degree=2)
print(training(train, test, answerTrain, answerTest))

clf = svm.SVC(kernel='poly',degree=1, coef0=1)
print(training(train, test, answerTrain, answerTest))

#the best one, polynomial kernel: (gamma <x, x'> + coef0) ^ degree,
#degree = 3, coef0 = 3, gamma = 0.0 => gamma = 1/n_features
clf = svm.SVC(kernel='poly', coef0=3)
print(training(train, test, answerTrain, answerTest))

#output the answer
a = open('output.txt', 'w')
for i in clf.predict(testing):
    a.write(str(int(i)) + "\n")
