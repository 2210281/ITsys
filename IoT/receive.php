<?php
//送られてきたPOSTデータを受け取って、JSONデータをデコードして$inに入れる
$json_string = file_get_contents('php://input');
$in = json_decode(stripslashes($json_string),true);

//送られてきたデータを取り出す
$value = $in["value"];  // = ごみ箱管理ID
$text = $in["text"];    // = ごみ箱が満杯です
//$_SERVER変数を使って送信元のIPアドレスを取得する
//レスポンスを取得したIPアドレスとし、それをJSONとして再度エンコード
//そして送信元(esp32)へ返す
$ipAddress = $_SERVER['REMORE_ADDR'];
//aws ELBを使用している場合はELBのIPアドレスを取得してしまうので
//以下のようにして元のIPアドレスを取得する
if(array_key_exists('HTTP_X_FORWARDED_FOR',$_SERVER)){
    $ipAddress = array_pop(explode(',', $_SERVER['HTTP_X_FORWARDED_FOR']));
}

//IPアドレスをエンコードして返す
echo json_encode($ipAddress)
?>