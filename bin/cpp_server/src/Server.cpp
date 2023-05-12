/*
** EPITECH PROJECT, 2023
** Server
** File description:
** vim > emacs
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <string>
#include <vector>
#include <stack>

#define PORT 4242

class Server {
    public:
        Server()
        {
        }
        ~Server()
        {
            close(this->_sock);
        }

        void createSocket()
        {
            _sock = socket(AF_INET, SOCK_STREAM, 0);
            if (_sock == -1) {
                std::cerr << "Error: socket creation failed" << std::endl;
                exit(84);
            }
        }

        void bindSocket()
        {
            _sin.sin_family = AF_INET;
            _sin.sin_port = htons(PORT);
            _sin.sin_addr.s_addr = htonl(INADDR_ANY);
            if (bind(_sock, (struct sockaddr *)&_sin, sizeof(_sin)) == -1) {
                perror("bind");
                exit(84);
            }
        }

        void listenSocket()
        {
            if (listen(_sock, 42) == -1) {
                std::cerr << "Error: listen failed" << std::endl;
                exit(84);
            }
        }

        void acceptSocket()
        {
            struct sockaddr_in csin;
            socklen_t sinsize = sizeof(csin);
            _csock = accept(_sock, (struct sockaddr *)&csin, &sinsize);
            if (_csock == -1) {
                std::cerr << "Error: accept failed" << std::endl;
                exit(84);
            }
        }

        std::string getDataFromClient()
        {
            char buffer[1024];
            int n = recv(_csock, buffer, 1024, 0);
            if (n == -1) {
                perror("read");
                exit(84);
            }
            buffer[n] = '\0';
            std::string data = buffer;
            return data;
        }

        void sendDataToClient(std::string data)
        {
            if (send(_csock, data.c_str(), data.size(), 0) == -1) {
                std::cerr << "Error: send failed" << std::endl;
                exit(84);
            }
        }

        std::string generateFormula()
        {
            std::vector<std::string> operators = {"+", "-", "*", "/"};
            std::vector<std::string> numbers = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
            std::string formula = "";
            int i = 0;
            while (i < 3) {
                formula += numbers[rand() % 10];
                formula += operators[rand() % 4];
                i++;
            }
            formula += numbers[rand() % 10];
            this->formula = formula;
            return this->formula;
        }

        void closeServer()
        {
            close(this->_csock);
        }

        bool isOperator(char c)
        {
            return (c == '+' || c == '-' || c == '*' || c == '/');
        }

        int doOperation(int a, int b, char op)
        {
            switch(op)
            {
                case '+': return a + b;
                case '-': return a - b;
                case '*': return a * b;
                case '/': return a / b;
                default: return 0;
            }
        }

        int eval(std::string expr)
        {
            std::stack<int> operands;
            std::stack<char> operators;

            for (size_t i = 0; i < expr.length(); i++)
            {
                char c = expr[i];

                if (isspace(c))
                    continue;
                else if (c == '(')
                    operators.push(c);
                else if (isdigit(c)) {
                    int num = 0;
                    while (i < expr.length() && isdigit(expr[i]))
                    {
                        num = (num * 10) + (expr[i] - '0');
                        i++;
                    }
                    i--;
                    operands.push(num);
                } else if (isOperator(c)) {
                    while (!operators.empty() && isOperator(operators.top()) &&
                           ((c != '*' && c != '/') || (operators.top() == '*' || operators.top() == '/'))) {
                        int b = operands.top();
                        operands.pop();
                        int a = operands.top();
                        operands.pop();
                        char op = operators.top();
                        operators.pop();
                        operands.push(doOperation(a, b, op));
                    }
                    operators.push(c);
                } else if (c == ')') {
                    while (!operators.empty() && operators.top() != '(') {
                        int b = operands.top();
                        operands.pop();
                        int a = operands.top();
                        operands.pop();
                        char op = operators.top();
                        operators.pop();
                        operands.push(doOperation(a, b, op));
                    }
                    operators.pop();
                }else {
                    std::cerr << "Error: invalid character '" << c << "'" << std::endl;
                    exit(1);
                }
            }
            while (!operators.empty())
            {
                int b = operands.top();
                operands.pop();
                int a = operands.top();
                operands.pop();
                char op = operators.top();
                operators.pop();
                operands.push(doOperation(a, b, op));
            }
            return operands.top();
        }
        std::string getFormula() const { return this->formula; }
        int getSocket() const { return this->_sock; }
    private:
        int _sock;
        struct sockaddr_in _sin;
        int _csock;
        std::string formula;
};

int main(void)
{
    Server server;

    srand(time(NULL));
    server.createSocket();
    server.bindSocket();
    server.listenSocket();
    server.acceptSocket();
    server.sendDataToClient(server.generateFormula());
    std::string data = server.getDataFromClient();
    if (server.eval(server.getFormula()) == std::stoi(data)) {
        std::cout << "Correct answer" << std::endl;
        server.sendDataToClient("1");
    } else {
        std::cout << "Wrong answer" << std::endl;
        server.sendDataToClient("0");
    }
    server.closeServer();
    return 0;
}
