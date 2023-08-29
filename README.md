# socket_test

抽象名前空間を使用したソケットを使用して、client からキー入力したデータを
server で受けてコンソールに表示する。
client を複数立ち上げても、一つの server で受けることができることを確認。

gcc server.c -o server
gcc client.c -o client


git init
git add README.md
git commit -m "first commit"
git branch -M main
git remote add origin https://github.com/room6502/socket_test.git
git push -u origin main
