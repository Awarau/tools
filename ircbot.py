import socket

HOST = "irc.freenode.org"
PORT = 6667
NICK = "fck1botbotbot234dfs21"
USERNAME = 'hellothere'
REALNAME = 'trial run'
CHAN = "#tryitout"

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))

nick = ('NICK ' + NICK + '\r\n').encode()
s.send(nick)
user = ('USER yo yo yo :tryitout \r\n').encode()
s.send(user)
join = ('JOIN ' + CHAN + '\r\n').encode()
s.send(join)

#to do: 
#keep the loop of reading on, without interruption from the send msg method
#implement PING PONG ritual

while 1:
        inputqueue = input("<" + NICK + "> ")
        msg = ("PRIVMSG " + CHAN + " :" + inputqueue + "\r\n").encode()
        s.send(msg)

        data = s.recv(4096).decode('utf-8')
        if data != ' ':
                print(data)
