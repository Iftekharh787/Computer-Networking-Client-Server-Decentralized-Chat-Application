//Client Program C Source code (Visual Studio 2008):

                  #include<winsock2.h>
                  #include<ws2tcpip.h>
                  #include<stdio.h>
                  #include<string.h>
                  #include<windows.h>

                  void rec_data(SOCKET hServer);
                  int nData=0;
                  struct data
                              {
                                    char  id_no[6];
                                    char name[15];
                                    char semester[5];
                                    char dis[15];
                              };
                  struct data database;


int main()

                        {

                              int idno=0;
                              int read=0,count=0;
                              char idno_s[5]={0};
                              char pass_con[30]={0};
                              char password[15]={0};
                              char data_check[15]={0};
                              char ipadd[15];



                  printf("please enter Ip address e.g: 172.16.64.58: ");
                  scanf("%s",ipadd);


            // Initialize WinSock2.2 DLL
            // low word = major, highword = minor

                        WSADATA wsaData = {0};
                        WORD wVer = MAKEWORD(2,2);

                        int nRet = WSAStartup( wVer, &wsaData );
                        if( nRet == SOCKET_ERROR )
                              {
                              printf( "\n Failed to init Winsock library" );
                                    return -1;
                              }

                        printf( "\n Opening connection to server" );
                        WORD WSAEvent = 0;
                        WORD WSAErr = 0;
                        SOCKET hServer = {0};

      // open a socket
      //
      // for the server we do not want to specify a network address
      // we should always use INADDR_ANY to allow the protocal stack
      // to assign a local IP address

      hServer = socket( AF_INET, SOCK_STREAM, IPPROTO_IP );
      if( hServer == INVALID_SOCKET )
            {
                  printf( "\n Invalid socket, failed to create socket" );
                  return -1;
            }


                        // name a socket

      hostent* localHost;
      char* localIP;
      localHost = gethostbyname("");
      localIP = inet_ntoa (*(struct in_addr *)*localHost->h_addr_list);

                        printf("\n\n%s\n\n",localHost->h_name);
                        sockaddr_in saServer = {0};
                        saServer.sin_family = PF_INET;
                        saServer.sin_port = htons( 10000 );

                        saServer.sin_addr.s_addr =inet_addr(ipadd);

                        // Resolve the server address and port

                        // connect

      nRet = connect( hServer, (sockaddr*)&saServer, sizeof( sockaddr ) );
            if( nRet == SOCKET_ERROR )
                  {
                        printf( "\n Connection to server failed\n" );
                        closesocket( hServer );
                        return -1;
                  }
printf( "\n\t\t================================================" );
printf( "\n\t\t\t Welcome to student Database" );
printf( "\n\t\t================================================" );

passagain:        printf("\n\n\n\tPlease enter the Password to login :>> ");
                        scanf("%s",password);
                        nData=send(hServer,password,sizeof(password),0);


                        nData=recv(hServer,pass_con,sizeof(pass_con),0);

                        if((strcmp(pass_con,"logged on"))==0)
                                    {
                                          printf("\n\n\tLogin Sucessfuly ");
                                          goto down;
                                    }
                        else if (count<5)
                        {
                              goto passagain;
                        }
                        else
                              goto END;
down:       printf("\n\n\tPlease enter Id No of student to view data: ");
                        scanf("%d",&idno);

                        sprintf(idno_s,"%d",idno);

                        nData=send(hServer,idno_s,5,0);

                        nData=recv(hServer,data_check,sizeof(data_check),0);

                        if((strcmp(data_check,"Data Found"))==0)
                              {

                                    printf("\n\t%s\n",data_check);
                                    rec_data(hServer);

                              }
                        else
                        printf("\n\nData Not Found\n");
END:

                        printf( "\n\tClosing connection\n" );
                        // shutdown socket
                        nRet = shutdown( hServer, SD_BOTH );
                        if( nRet == SOCKET_ERROR ) {
                        // WSAGetLastError()
                        printf( "\n Error trying to perform shutdown on socket" );
                        return -1;
                        }
                        // close server socket
                        nRet = closesocket( hServer );
                        hServer = 0;
                        if( nRet == SOCKET_ERROR ) {
                        printf( "\n Error failed to close socket" );
                        }
                        // Release WinSock DLL
                        nRet = WSACleanup();
                        if( nRet == SOCKET_ERROR ) {
                        printf( "\n Error cleaning up Winsock Library" );
                        return -1;
                        }

                        return 0;
                        }



void rec_data(SOCKET hServer)
{
      nData=recv(hServer,database.id_no,sizeof(database.id_no),0);
      nData=recv(hServer,database.name,sizeof(database.name),0);
      nData=recv(hServer,database.semester,sizeof(database.semester),0);
      nData=recv(hServer,database.dis,sizeof(database.dis),0);

      printf("\n\tID Number  :>> %s",database.id_no);
      printf("\n\tName       :>> %s",database.name);
      printf("\n\tSemester   :>> %s",database.semester);
      printf("\n\tDiscipline :>> %s",database.dis);

}
