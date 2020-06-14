from flask import Flask, jsonify, request
from flask import render_template
import ast

app = Flask(__name__)

labels = []
values_pos = []
values_neu = []
values_neg = []

@app.route("/")
def get_chart_page():
    global labels, values_pos, values_neu, values_neg
    labels = []
    values_pos = []
    values_neu = []
    values_neg = []

    # labels = ["#bunkerbitch", "#bunkerboy", "#fakepresident", "#trumpresignnow", "#resignnowtrump", "#bunkerbaby", "#protests2020", "#blacklivesmatter", "#anonymous", "#maga"]
    # values_pos = ["155","103","47","23","23","31","17","20","14","34"]
    # values_neu = ["353","189","83","58","24","39","30","16","26","25"]
    # values_neg = ["367","227","164","113","95","37","49","58","53","34"]
    return render_template('chart.html', values_pos=values_pos, values_neu=values_neu, values_neg=values_neg, labels=labels)

@app.route('/refreshData')
def refresh_graph_data():
    global labels, values_pos, values_neu, values_neg
    # print("labels now: " + str(labels))
    # print("data now: " + str(values_pos))
    # print("data now: " + str(values_neu))
    # print("data now: " + str(values_neg))

    return jsonify(sLabel=labels, sData_pos=values_pos, sData_neu=values_neu, sData_neg=values_neg)

@app.route('/updateData', methods=['POST'])
def update_data_post():
    global labels, values_pos, values_neu, values_neg
    if not request.form:
        return "error", 400
    labels = ast.literal_eval(request.form['label'])
    values_pos = ast.literal_eval(request.form['data_pos'])
    values_neu = ast.literal_eval(request.form['data_neu'])
    values_neg = ast.literal_eval(request.form['data_neg'])

    # print("labels received: " + str(labels))
    # print("data received: " + str(values_pos))
    # print("data received: " + str(values_neu))
    # print("data received: " + str(values_neg))
    return "success", 201


if __name__ == "__main__":
    app.run(host='localhost', port=5001)