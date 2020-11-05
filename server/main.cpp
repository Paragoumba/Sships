#include <libssh/libssh.h>
#include <libssh/server.h>
#include <iostream>
#include <csignal>
#include <vector>
#include <ncurses.h>
#include <cmath>

#define KEYS_FOLDER "/etc/ssh/"

bool running = true;

void exitHandler(int){

    running = false;

}

int main(){

    signal(SIGINT, exitHandler);

    int p[2];

    if (pipe(p) == -1){

        std::cout << "Error when trying to open pipe." << std::endl;

    }

    pid_t pid = fork();

    switch (pid){
        case -1:
            std::cerr << "Fork error." << std::endl;
            return 1;

        default:
            if (dup2(p[1], 1) == -1){

                std::cout << "dup write failed." << std::endl;
                return 1;

            }

            initscr();
            curs_set(0);
            printw("[");

            for (int i = 1; i <= 73; ++i){

                mvprintw(0, i, ".");

            }

            mvprintw(0, 74, "]   0%%");
            refresh();

            for (int i = 1; i <= 73; ++i){

                sleep(1);

                int percentage = static_cast<int>(round((double) i / 73 * 100));

                if (percentage > 99){

                    mvprintw(0, 76, std::to_string(percentage / 100 % 10).c_str());

                }

                if (percentage > 9){

                    mvprintw(0, 77, std::to_string(percentage / 10 % 10).c_str());

                }

                mvprintw(0, 78, std::to_string(percentage % 10).c_str());
                mvprintw(0, i, "#");
                refresh();

            }

            sleep(1);

            endwin();
            break;

        case 0:
            std::vector<std::string> users;

            const char* address = "127.0.0.1";
            const int port = 6666;

            if (dup2(p[0], 0) == -1){

                std::cout << "dup read failed." << std::endl;
                return 1;

            }

            ssh_bind sshbind = ssh_bind_new();
            ssh_session session = ssh_new();

            ssh_bind_options_set(sshbind, SSH_BIND_OPTIONS_BINDADDR, address);
            ssh_bind_options_set(sshbind, SSH_BIND_OPTIONS_BINDPORT, &port);
            ssh_bind_options_set(sshbind, SSH_BIND_OPTIONS_DSAKEY, KEYS_FOLDER "battleship_server_dsa_key");
            ssh_bind_options_set(sshbind, SSH_BIND_OPTIONS_RSAKEY, KEYS_FOLDER "battleship_server_rsa_key");

            if(ssh_bind_listen(sshbind) < 0){

                std::cout << "Error listening to socket: " << ssh_get_error(sshbind) << std::endl;
                return 1;

            }

            int r = ssh_bind_accept(sshbind, session);

            if(r == SSH_ERROR){

                std::cout << "Error accepting a connection: " << ssh_get_error(sshbind) << std::endl;
                return 1;

            }

            if (ssh_handle_key_exchange(session)){

                std::cout << "ssh_handle_key_exchange: " << ssh_get_error(session) << std::endl;
                return 1;

            }

            std::cout << "Connected." << std::endl;

            std::string username;
            ssh_message message;
            int auth = 0;

            do {

                message = ssh_message_get(session);

                if(!message){

                    break;

                }

                switch(ssh_message_type(message)){

                    case SSH_REQUEST_AUTH:
                        username = ssh_message_auth_user(message);

                        if (std::find(users.begin(), users.end(), username) == users.end()){

                            users.push_back(username);

                            ssh_message_auth_reply_success(message, 0);
                            ssh_message_auth_set_methods(message, SSH_AUTH_METHOD_NONE);

                            auth = 1;

                            break;

                        }

                    default:
                        ssh_message_reply_default(message);

                }

                ssh_message_free(message);

            } while (!auth);

            ssh_channel chan = nullptr;

            do {

                message = ssh_message_get(session);

                if(message){

                    switch(ssh_message_type(message)){

                        case SSH_REQUEST_CHANNEL_OPEN:
                            if(ssh_message_subtype(message) == SSH_CHANNEL_SESSION){

                                chan = ssh_message_channel_request_open_reply_accept(message);
                                break;

                            }

                        default:
                            ssh_message_reply_default(message);

                    }

                    ssh_message_free(message);

                }

            } while(message && !chan);

            if(!chan){

                std::cout << "Error: " << ssh_get_error(session) << std::endl;
                ssh_finalize();

                return 1;

            }

            std::string s;

            while(std::getline(std::cin, s)){

                ssh_channel_write(chan, s.c_str(), s.size() - 1);

            }

            ssh_disconnect(session);
            ssh_bind_free(sshbind);
            ssh_finalize();
            break;

    }
}