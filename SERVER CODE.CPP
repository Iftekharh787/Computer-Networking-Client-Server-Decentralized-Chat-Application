//Server Program C Source code (Visual Studio 2008):
          #include<bits/stdc++.h>
            #include<winsock2.h>
            #include<stdio.h>
            #include<windows.h>
            #include<string.h>
            #include<dos.h>

            void send_data(SOCKET hClient, char id_no[6]);
            void error(SOCKET hClient);
            void wait();


struct info
                  {
                        int id_no;
                        char name[15];
                        char semester[5];
                        char depart[15];
                  };
            struct info data;

            int nData=0;

            int main()
            {

                  int count=0 ;
                  FILE *ptr;

                  int file_size=0;
                  int id=0;
                  int flag=0;
                  float size=0;
                  int end=0;
                  char buf[800] = {0};
                  char  pass[15]={0};
                  char pass_not[20]="password invalid";
                  char pass_valid[20]="logged on";
                  char id_no[6]={0};

printf( "\n\t\t================================================" );
printf( "\n\t\t\t Welcome to student Database Server" );
printf( "\n\t\t================================================" );


      WSADATA wsaData = {0};        // Initialize WinSock2.2 DLL
      WORD wVer = MAKEWORD(2,2);    // low word = major, highword = minor

                  int nRet = WSAStartup( wVer, &wsaData );

                  if( nRet == SOCKET_ERROR )
                        {
                              // WSAGetLastError()
                              printf( "\nFailed to init Winsock library" );                                 return -1;
                        }

                  printf( "\n\n\n\t\tStarting server\n" );

                  // name a socket

                  WORD WSAEvent = 0;
                  WORD WSAErr = 0;


            // open a socket

            // for the server we do not want to specify a network address
            // we should always use INADDR_ANY to allow the protocal stack
            // to assign a local IP address

                  SOCKET hSock = {0};
                  hSock = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );

                  if( hSock == INVALID_SOCKET )
                        {
                              printf( "\t\nInvalid socket, failed to create socket" );
                              return -1;
                        }


                  // name socket
                  sockaddr_in saListen = {0};
                  saListen.sin_family = PF_INET;
                  saListen.sin_port = htons( 10000 );
                  saListen.sin_addr.s_addr = htonl( INADDR_ANY );


                  // bind socket's name
            nRet = bind( hSock, (sockaddr*)&saListen, sizeof(sockaddr) );

                  if( nRet == SOCKET_ERROR )
                        {
                              printf( "\t\nFailed to bind socket" );
                              //shutdown( hSock );

                              closesocket( hSock );
                              return -1;
                        }


      while( true )
            {
            printf( "\n\t\tListening for connections\n" );  // listen
            nRet = listen( hSock, 5 );// connection backlog queue set to 10

      if( nRet == SOCKET_ERROR )
            {
                  int nErr = WSAGetLastError();
                  if( nErr == WSAECONNREFUSED )
                  {
                        printf( "\nFailed to listen, connection refused" );
                  }

      else
            {
            printf( "\nCall to listen failed" );
            }
            closesocket( hSock );
            return -1;
      }


                              // connect

                  sockaddr_in saClient = {0};

                  int nSALen = sizeof( sockaddr );

                  SOCKET hClient={0};
                  hClient = accept( hSock, (sockaddr*)&saClient, &nSALen );

      if( hClient == INVALID_SOCKET )
            {
                  printf( "\nInvalid client socket, connection failed\n" );
                  closesocket( hSock );
                  return -1;
            }

                  printf( "\n\t\tConnection estabilished" );


again:nData=recv(hClient,pass,sizeof(pass),0);  // sending download msg

                  if ((strcmp(pass,"NUST"))!=0&& count<5)
                        {
                              count++;
                            int  Data=send(hClient,pass_not,sizeof(pass_not),0);
                              goto again;
                        }
                  else if ((strcmp(pass,"NUST"))==0)
                        {
                              nData=send(hClient,pass_valid,sizeof(pass_valid),0);
      goto down;
                        }
                  else
                        goto END;


down:       printf("\n \n\t\t:>> User logged in\n\n");

                  if((ptr=fopen("database.txt","rb+"))==NULL)
                  {
                        printf("\n File error\n");
                  }

                  nData=recv(hClient,id_no,sizeof(id_no),0);

                  id=atoi(id_no);

                  fseek(ptr,0L,SEEK_SET);

                  do
                  {
                        fread(&data,sizeof(data),1,ptr);

                        if(data.id_no==id)
                        {
                              flag=1;
                              break;
                        }


                  }while(feof(ptr)==0);

                  if(flag==1)
                  {
                  send_data(hClient,id_no);
                  flag=0;
                  nData=recv(hClient,cont,sizeof(cont),0);
                  if((strcmp(cont,"y"))==0||(strcmp(cont,"Y"))==0)
                              {
                                    goto again;
                              }
                  }
                  else
                  {
                  error(hClient);
                  }

            END:
                  closesocket( hClient );             // close client connection
                  end++;
                  if(end==10)
                        break;

                  }

                  printf( "\nShutting down the server" );

                  nRet = closesocket( hSock );    // close server socket
                  hSock = 0;


                  if( nRet == SOCKET_ERROR )
                        {
                              printf( "\nError failed to close socket" );
                        }
                  nRet = WSACleanup();          // Release WinSock DLL


                  if( nRet == SOCKET_ERROR )
                        {
                              printf( "\nError cleaning up Winsock Library" );
                              return -1;
                        }
                  printf( "\nServer is offline" );

                  return 0;                     // shut down

}


void send_data(SOCKET hClient,char id_no[6])
                  {
                        char d_found[15]="Data Found";
                        printf("\n\tSending The Record:>>");
                        printf("\n\t\t\t\t%d",data.id_no);
                        printf("\n\t\t\t\t%s",data.name);
                        printf("\n\t\t\t\t%s",data.semester);
                        printf("\n\t\t\t\t%s",data.depart);
                        nData=send(hClient,d_found,sizeof(d_found),0);
                        wait();
                        nData=send(hClient,id_no,sizeof(id_no),0);
                        wait();
                        nData=send(hClient,data.name,sizeof(data.name),0);
                        wait();
                        nData=send(hClient,data.semester,sizeof(data.semester),0);
                        wait();
                        nData=send(hClient,data.depart,sizeof(data.depart),0);
                        wait();
                  }


void error(SOCKET hClient)
            {
                        char d_error[20]="Data  Not Found";
                        wait();
                        nData=send(hClient,d_error,sizeof(d_error),0);
            }


void wait()
{
      unsigned int delay;
      for(delay=0;delay<=100000000;delay++)
      {

      }

}
