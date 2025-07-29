#include "Calculator.h"

unordered_map<string, int> operators {
    {"+", 1},
    {"-", 1},
    {"*", 2},
    {"/", 2},
    {"^", 3}
};

int main() {
    string input = "\0";
    string token = "\0";
    char tokench = '\0';
    cout<<"Введите операцию: "<<endl;
    getline(cin, input);
    istringstream inputstream(input);
    if(!(isCorrectInput(inputstream))) {
        cout<<"Некорректный ввод! "<<endl;
        return 0;
    }
    stack<string> opStack; // стак операторов2+
    queue<string> outputQueue; // выходная очередь
    while(inputstream>>tokench) {
        string topValue = "\0";
        token = tokench;
        if(token == "(") {
            opStack.push(token);
        }
        else if(token == ")") {
            while(opStack.top() != "(") {
                outputQueue.push(opStack.top());
                opStack.pop();
            }
            opStack.pop();
        }
        else if(isdigit(token[0])) {      // обработка чисел. Попытка обрабатывать числа с более чем одним символом.
            inputstream.putback(token[0]);
            string num;
            while(inputstream.get(token[0]) && isdigit(token[0]))
                num +=token[0];
            outputQueue.push(num);
            num = "/0";
            inputstream.putback(token[0]);
        }
        else if(operators.find(token) != operators.end() && opStack.empty())
            opStack.push(token);
        else if(operators.find(token) != operators.end()) {
            topValue = opStack.top();
            cout<<token<<" - "<<operators[token]<<"     "<<topValue<<" - "<<operators[topValue]<<endl;
            if(operators[token] <= operators[topValue]) {
                outputQueue.push(opStack.top());
                opStack.pop();
                opStack.push(token);
            }
            else
                opStack.push(token);
        }
    }
    while(!(opStack.empty()))
        {
            outputQueue.push(opStack.top());
            opStack.pop();
        }

    if(stod(Sort(outputQueue, opStack)) == stoi(Sort(outputQueue, opStack))) {
         cout<<stoi(Sort(outputQueue, opStack))<<endl;
    }
    else
        cout<<fixed<<setprecision(2)<<stod(Sort(outputQueue, opStack))<<endl;
    return 0;
}


 string Sort(queue<string>& otQueue,stack<string>& opStack) {
        double leftValue = 0, rightValue = 0;
        string op = "\0";
        while(!(otQueue.empty())) {
            if(isdigit(otQueue.front()[0])) {
                opStack.push(otQueue.front());
                otQueue.pop();
            }
            else {
                op = otQueue.front();
                otQueue.pop();
                rightValue = stod(opStack.top());
                opStack.pop();
                leftValue = stod(opStack.top());
                opStack.pop();
                opStack.push(Calculate(leftValue, op, rightValue));
                rightValue = 0;
                leftValue = 0;
            }
        }
        return opStack.top();
        }

string Calculate(double& leftValue, string& op, double& rightValue) {
    switch(op[0]) {
        case '+':
        return to_string(leftValue + rightValue);
        case '-':
        return to_string(leftValue - rightValue);
        case '*':
        return to_string(leftValue * rightValue);
        case '/':
        if(rightValue == 0) {
            cout<<"Делить на ноль нельзя"<<endl;
            return 0;
        }
        else
        return to_string(leftValue/rightValue);
        default:
            cout<<"неверный ввод"<<endl;
            return 0;
    }
} 
 

bool isCorrectInput(istringstream& iss) {
    string strValue;
    char streamValue = '\0';
    bool isOperator = false;
    while(iss>>streamValue) {
            strValue = streamValue;
        if(isalpha(streamValue))
            return false;
        else if(operators.find(strValue) != operators.end()) {
            if(isOperator)
                return false;
            isOperator = true;
        }
    }
    return true;
}