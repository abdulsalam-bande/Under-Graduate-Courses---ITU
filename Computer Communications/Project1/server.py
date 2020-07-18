
import select
import datetime
import sys
import socket
from threading import Thread
import time



class user:
    def __init__(self,ip,name):
        self.ip = ip
        self.name = name

class clinet:
    def __init__(self,socket_number,date):
        self.socket_number = socket_number
        self.date = date



if __name__ == "__main__":
    #to date messages to other clients
    def send_to_all_of_my_clients(my_socket, my_message):
    #To avoid sending data to the sending client
        for socket in dictionary_of_clients:
            if socket != socket_of_my_server and socket != my_socket :
                socket.send(my_message.encode('utf-8'))




    socket_of_my_server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    second = 45
    #name_dic = {}
    #username = input("Please enter your username\n")
    socket_of_my_server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    #name_dic = {}
    socket_of_my_server.bind(("0.0.0.0", 3823))
    name_adate3 = {}
    socket_of_my_server.listen(20)
    dictionary_of_clients = []
    dictionary_of_clients.append(socket_of_my_server)
    cleintdate = {}
    clientinfo = {}
    first = 30

    print ("This server is activated on port " + str(3823))

    while 200>10:
        # Get of the connected clients
        read_sockets,write_sockets,error_sockets = select.select(dictionary_of_clients,[],[])

        for my_socket in read_sockets:
            if my_socket == socket_of_my_server:
                sockfd, client_information = socket_of_my_server.accept()
                strange,ip = client_information
                cleintdate[strange] = ip
                clientinfo[ip] =strange
                dictionary_of_clients.append(sockfd)
                #timenow = str(datetime.datetime.now())
                datenow = str(datetime.datetime.now())
                
                #print(str(username) + "is connected\n")
                
                if first>second:
                    sockfd, client_information = socket_of_my_server.accept()
                    print(cleintdate[ip] + " Is now connected\n" )
                    strange,ip = client_information
                    print("Message sent by---->" +str(cleintdate[ip]))
                print("Client (%s, %s) connected  " % client_information +str(" at time ")+str(datenow))
                send_to_all_of_my_clients(sockfd,  "\n[%s:%s] is Online\n"  % client_information)
        
            #To send data to the server
            else:
                data = my_socket.recv(65536)
                data = data.decode('utf_8')
                if data:
                    timenow = time.strftime("%H:%M:%S")
                    #print("Message from ")
                    send_to_all_of_my_clients(my_socket, "\r"  + str(my_socket.getpeername()) + " at " + str(timenow)+ ': ' + data )



