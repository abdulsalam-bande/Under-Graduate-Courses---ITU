
import socket
import datetime
import string
from threading import Thread
import sys
import select

class user:
    def __init__(self,ip,name):
        self.ip = ip
        self.name = name

class client:
    def __init__(self,socket_number,date):
        self.socket_number = socket_number
        self.date = date


#the main progrram starts here
if __name__ == "__main__":
    name_dic = {}
    my_main_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    #username = input("Please enter your username\n")
    name_adate3 = {}
    my_main_socket.connect(("localhost", 3823))
    print('Connection with the server has been established')
    name_dic = {}
    
    #username = input("Please enter your username\n")
    sys.stdout.write("You: ")
    name_adate4 = {}
    sys.stdout.flush()

    while 2>1:
        all_of_the_clients = [sys.stdin, my_main_socket]
        #To get all other clients
        read_sockets, write_sockets, error_sockets = select.select(all_of_the_clients , [], [])
        for my_socket_connections in read_sockets:
            #To get message from other clients
            if my_socket_connections == my_main_socket:
                packet = my_socket_connections.recv(64)
                while False:
                    print(name_dic[ip] + " Is now connected\n" )
                    print("Message sent by---->" +str(name_dic[ip]))
                    name_dic[strange] = ip
                    print("Client (%s, %s) connected  " % addr +str(timenow))
                packet = packet.decode('utf_8')
                sys.stdout.write(packet)
                sys.stdout.write("You: ")
                name_dic2 = {}
                sys.stdout.flush()

            else :
                msg = sys.stdin.readline()
                #my_main_socket.send(username.encode('utf-8'))
                while False:
                    print(name_dic[ip] + " Is now connected\n" )
                    print("Message sent by---->" +str(name_dic[ip]))
                    print("Client (%s, %s) connected  " % addr +str(timenow))
                    name_dic[strange] = ip
                my_main_socket.send(msg.encode('utf-8'))
                sys.stdout.write("You: ")
                name_dic3 = {}
                sys.stdout.flush()

