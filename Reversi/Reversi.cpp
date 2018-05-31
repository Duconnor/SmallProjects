//
//  Reversi.cpp
//  ReversiClient
//
//  Created by ganjun on 2018/3/6.
//  Copyright © 2018年 ganjun. All rights reserved.
//

#include "Reversi.h"

#define random(x) (rand()%x)
#define ROWS 8
#define COLS 8
#define ROUNDS 10

Reversi::Reversi() {
    // client_socket = ClientSocket();
    oppositeColor = ownColor = -1;
    board = Board();
}

Reversi::~Reversi() {};

/*
 send id and password to server by socket
 rtn != 0 represents socket transfer error
 */
int Reversi::authorize(const char *id, const char *pass) {
    client_socket.connectServer();
    std::cout << "Authorize " << id << std::endl;
    char msgBuf[BUFSIZE];
    memset(msgBuf, 0, BUFSIZE);
    msgBuf[0] = 'A';
    memcpy(&msgBuf[1], id, 9);
    memcpy(&msgBuf[10], pass, 6);
    int rtn = client_socket.sendMsg(msgBuf);
    if (rtn != 0) {
        printf("Authorized Failed!\n");
        return -1;
    }
    return 0;
}

// 用户id输入，服务器上需要有对应的账号密码：对应文件 players-0.txt
void Reversi::gameStart() {
    char id[12] = {0}, passwd[10] = {0};
    //char id[12] = "111111110", passwd[10] = "123456";
    printf("ID: %s\n", id);
    scanf("%s", id);
    printf("PASSWD: %s\n", passwd);
    scanf("%s", passwd);

    int auth = authorize(id, passwd);
    if (auth < 0) {
        return;
    }
    printf("Game Start!\n");
    board.printOut(false, true);

    for (int round = 0; round < ROUNDS; round++) {
        roundStart(round);
        oneRound();
        roundOver(round);
        board.clearRestricted();
        board.printOut();
        board.printOut(true, false);
    }
    gameOver();
    client_socket.close();
}

void Reversi::gameOver() {
    printf("Game Over!\n");
}

// 发一次消息，走哪一步，等两个消息，1.自己的步数行不行 2. 对面走了哪一步
void Reversi::roundStart(int round) {
    printf("Round %d Ready Start!\n", round);

    // first time receive msg from server
    int rtn = client_socket.recvMsg();
    if (rtn != 0) return;
    if (strlen(client_socket.getRecvMsg()) < 2)
        printf("Authorize Failed!\n");
    else
        printf("Round start received msg %s\n", client_socket.getRecvMsg());
    switch (client_socket.getRecvMsg()[1]) {
        // this client : black chessman
        case 'B':
            ownColor = 0;
            board.setColor(ownColor);
            oppositeColor = 1;
            rtn = client_socket.sendMsg("BB");
            printf("Send BB -> rtn: %d\n", rtn);
            if (rtn != 0) return;
            break;
        case 'W':
            ownColor = 1;
            board.setColor(ownColor);
            oppositeColor = 0;
            rtn = client_socket.sendMsg("BW");
            printf("Send BW -> rtn: %d\n", rtn);
            if (rtn != 0) return;
            break;
        default:
            printf("Authorized Failed!\n");
            break;
    }
    //chess board init
    initChessBoard();
}

void Reversi::oneRound() {
    int STEP = 1;
    switch (ownColor) {
        case 0:
            while (STEP < 10000) {

                pair<int, int> chess = step();                        // take action, send message

                // lazi only excute after server's message confirm  in observe function
                generateOneStepMessage(chess.first, chess.second);


                if (observe() >= 1) break;     // receive RET Code

                if (observe() >= 1) break;    // see white move
                STEP++;
                board.roundCount++;
                saveChessBoard();
            }
            printf("One Round End\n");
            break;
        case 1:
            while (STEP < 10000) {

                if (observe() >= 1) break;    // see black move

                pair<int, int> chess = step();                        // take action, send message
                // lazi only excute after server's message confirm  in observe function
                generateOneStepMessage(chess.first, chess.second);


                if (observe() >= 1) break;     // receive RET Code
                saveChessBoard();
                board.roundCount++;
                STEP++;
            }
            printf("One Round End\n");
            break;

        default:
            break;
    }
    printf("One Round end ###################\n");
}

void Reversi::roundOver(int round) {
    printf("Round %d Over!\n", round);
    // reset initializer

    ownColor = oppositeColor = -1;
}

int Reversi::observe() {
    int rtn = 0;
    int recvrtn = client_socket.recvMsg();
    if (recvrtn != 0) return 1;
    printf("receive msg %s\n", client_socket.getRecvMsg());
    switch (client_socket.getRecvMsg()[0]) {
        case 'R': {
            switch (client_socket.getRecvMsg()[1]) {
                case 'Y':   // valid step
                    switch (client_socket.getRecvMsg()[2]) {
                        case 'P':   // update chessboard
                        {
                            int desRow =
                                    (client_socket.getRecvMsg()[3] - '0') * 10 + client_socket.getRecvMsg()[4] - '0';
                            int desCol =
                                    (client_socket.getRecvMsg()[5] - '0') * 10 + client_socket.getRecvMsg()[6] - '0';
                            int color = (client_socket.getRecvMsg()[7] - '0');
                            handleMessage(desRow, desCol, color);

                            printf("a valid step of : (%d %d)\n", desRow, desCol);
                            break;
                        }
                        case 'N':   // RYN: enemy wrong step
                        {
                            //
                            printf("a true judgement of no step\n");
                            int desRow = -1;
                            int desCol = -1;

                            int color = (client_socket.getRecvMsg()[3] - '0');
                            handleMessage(desRow, desCol, color);
                            break;
                        }
                    }

                    break;
                case 'W':
                    // invalid step
                    switch (client_socket.getRecvMsg()[2]) {
                        case 'P': {
                            int desRow =
                                    (client_socket.getRecvMsg()[3] - '0') * 10 + client_socket.getRecvMsg()[4] - '0';
                            int desCol =
                                    (client_socket.getRecvMsg()[5] - '0') * 10 + client_socket.getRecvMsg()[6] - '0';

                            int color = (client_socket.getRecvMsg()[7] - '0');
                            printf("Invalid step , server random a true step of : (%d %d)\n", desRow, desCol);
                            handleMessage(desRow, desCol, color);
                            break;
                        }
                        case 'N': {
                            printf("a wrong judgement of no step\n");
                            int desRow = -1;
                            int desCol = -1;

                            int color = (client_socket.getRecvMsg()[3] - '0');
                            handleMessage(desRow, desCol, color);
                            break;
                        }
                        default:
                            break;
                    }
                    break;
                case '1':

                    printf("Error -1: Msg format error!\n");
                    rtn = -1;
                    break;
                case '2':

                    printf("Error -2: Corrdinate error!\n");
                    rtn = -2;
                    break;
                case '4':

                    printf("Error -4: Invalid step!\n");
                    rtn = -4;
                    break;
                default:

                    printf("Error -5: Other error!\n");
                    rtn = -5;
                    break;
            }
            break;
        }
        case 'E': {
            switch (client_socket.getRecvMsg()[1]) {
                case '0':
                    // game over
                    rtn = 2;
                    break;
                case '1':
                    // round over
                    rtn = 1;
                default:
                    break;
            }
            break;
        }
        default:
            break;
    }
    return rtn;
}

void Reversi::generateOneStepMessage(int row, int col) {
    char msg[BUFSIZE];
    memset(msg, 0, sizeof(msg));

    //put row and col in the message
    msg[0] = 'S';
    msg[1] = 'P';
    msg[2] = '0' + row / 10;
    msg[3] = '0' + row % 10;
    msg[4] = '0' + col / 10;
    msg[5] = '0' + col % 10;
    msg[6] = '\0';
    if (row < 0 || col < 0) row = -1, col = -1;
    if (row == -1 && col == -1) {
        msg[2] = '-';
        msg[3] = '1';
        msg[4] = '-';
        msg[5] = '1';
    }

    //print
    printf("generate one step at possition (%2d,%2d) : %s\n", row, col, msg);

    client_socket.sendMsg(msg);
}

/*-------------------------last three function--------------------------------
 * startNewRound(function): start a new Round, init your chessboard
 * step(function) : find a good position to lazi your chess.
 * saveChessBoard(function) : save the chess board now.
 * handleMessage(function): handle the message from server.
 * initChessBoard(function): start a new round , initially your chessboard
 * ownColor(variable): present your chessman color，0 present black，1 present white
 */
pair<int, int> Reversi::step() {
    //此处写算法
    int row = -1, col = -1;
//    algorithm.minMaxSearch(true, board, INT32_MIN, INT32_MAX, algorithm.SEARCHDEPTH, ownColor, row, col);
    int guessVal = algorithm.minMaxSearch(true, board, INT32_MIN, INT32_MAX, algorithm.SEARCHDEPTH, ownColor, row, col);
    //algorithm.MTD_f(true, board, row, col, board.calculateValue(), ownColor);
    return make_pair(row, col);
}


void Reversi::saveChessBoard() {
    board.printOut();
}

void Reversi::handleMessage(int row, int col, int color) {
    cout << "********************************************" << endl;
    cout << "in hadnleMessage: color: " << color << " " << "pos: " << "(" << row << "," << col << ")" << endl;
    board.placeChessman(row, col, color);
}

//init your chess board here
void Reversi::initChessBoard() {
    board.clear();
}

