import urequests
import ujson

#送信先のURLの指定
#"XXX.XXX.XXX.XXX"にURLを入れる
url = 'http://XXX.XXX.XXX.XXX/receive.php'

#データをDICT型で宣言
obj = {"value": 123, "text": "abc"}

#jsonデータで送信するということを明示的に宣言する
header = {'Content-Type':'application/json'}

#オブジェクトをJSONに変換し、HTTPリクエストをPOSTとして送信
res = utrequests.post(
    url,
    data = ujson.dumps(obj).encode("utf-8"),
    headers = header
    )
#サーバ側からのレスポンスを受け取って表示(jsonのでコードも一緒にしている)
print(res.json())

#終了
res.close()