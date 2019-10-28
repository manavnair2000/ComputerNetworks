import socket

f=open("downloaded_webpage.html",'w')

target = str(input("Enter Domain :"))

port = 80  # create a socket object
soc = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# connect the c
soc.connect((target,port))

# send some data
request =  "GET /index.html HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n" % target
soc.send(request.encode())
header = "Connection: close"
# receive some data
while True:
    http_response = soc.recv(4096)
    http_response_len = len(http_response)
    if http_response is b'':
        break
    html = str(http_response.decode('ISO-8859-1'))
    pos = html.find(header)
    if pos > 0:
        f.write(html[pos+len(header):])
    else:
        f.write(html)

#display the response
print("file successfully downloaded")
