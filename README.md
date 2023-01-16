# philosophers
https://user-images.githubusercontent.com/38822155/212701057-c53ce35e-29cc-4919-8964-808316a42f5e.mp4

## 概要
- 「食事する哲学者の問題」を実行するプログラム
- ms単位での検証
- 負荷の高い数値を入力するとマシンスペックによって結果が異なるため理論値は難しい。
## 使い方
```
cd philo
make
./philo [哲学者の人数] [哲学者が最後の食事をしてから死ぬまでの時間] [食事時間] [睡眠時間]  [終了する食事回数（オプション）]

ex
./philo 4 200 60 60 1

:output
1673878975300 3 has taken a fork
1673878975300 3 has taken a fork
1673878975300 3 is eating
1673878975300 1 has taken a fork
1673878975300 1 has taken a fork
1673878975300 1 is eating
1673878975360 1 is sleeping
1673878975360 4 has taken a fork
1673878975360 3 is sleeping
1673878975360 2 has taken a fork
1673878975360 2 has taken a fork
1673878975360 2 is eating
1673878975360 4 has taken a fork
1673878975360 4 is eating

```
