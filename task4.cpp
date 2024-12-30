#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;

string toLowerCase(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

unordered_map<string, vector<string>> responses = {
    {"hello", {"Hi there!", "Hello! How can I assist you?", "Hey! What can I do for you today?"}},
    {"bye", {"Goodbye! Have a great day!", "See you later!", "Take care!"}},
    {"how are you", {"I'm just a bot, but I'm doing well. How about you?", "I'm doing great! What about you?"}},
    {"name", {"I am an AI chatbot. You can call me anything you like!", "I don't have a name, but feel free to name me!"}},
    {"thank you", {"You're welcome!", "Glad I could help!", "Happy to assist!"}},
    {"default", {"Sorry, I didn't quite get that.", "Can you please clarify?", "I'm not sure how to respond to that."}},
};

string analyzeSentiment(string input) {
    string sentiment = "Neutral";
    vector<string> positiveWords = {"good", "great", "awesome", "excellent", "happy"};
    vector<string> negativeWords = {"bad", "sad", "angry", "upset", "horrible"};

    input = toLowerCase(input);

    for (const string& word : positiveWords) {
        if (input.find(word) != string::npos) {
            sentiment = "Positive";
            break;
        }
    }

    for (const string& word : negativeWords) {
        if (input.find(word) != string::npos) {
            sentiment = "Negative";
            break;
        }
    }

    return sentiment;
}

string getResponse(string input) {
    input = toLowerCase(input);

    if (responses.find(input) != responses.end()) {
        return responses[input][rand() % responses[input].size()];
    }

    return responses["default"][rand() % responses["default"].size()];
}

int main() {
    srand(time(0));
    string userInput;
    string userName = "";
    bool userAskedName = false;

    while (true) {
        cout << "You: ";
        getline(cin, userInput);

        userInput = toLowerCase(userInput);

        if (userInput == "bye") {
            cout << "AI Chatbot: Goodbye! Have a great day!" << endl;
            break;
        }

        if (userInput.find("my name is") != string::npos && !userAskedName) {
            userName = userInput.substr(userInput.find("is") + 2);
            userName = toLowerCase(userName);
            userName = userName.substr(0, userName.find(" "));
            userAskedName = true;
            cout << "AI Chatbot: Nice to meet you, " << userName << "!" << endl;
            continue;
        }

        string sentiment = analyzeSentiment(userInput);

        if (userInput.find("what is") != string::npos) {
            if (userInput.find("your name") != string::npos) {
                cout << "AI Chatbot: I am just an AI, I don't have a specific name. But you can call me anything you like!" << endl;
                continue;
            }
            if (userInput.find("weather") != string::npos) {
                cout << "AI Chatbot: I cannot fetch real-time weather, but you can check a weather app!" << endl;
                continue;
            }
        }

        string response = getResponse(userInput);

        if (userAskedName && userInput != "bye") {
            cout << "AI Chatbot: Hello, " << userName << "! " << response << endl;
        } else {
            cout << "AI Chatbot: " << response << endl;
        }
    }

    return 0;
}
