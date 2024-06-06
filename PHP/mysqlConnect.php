<?php




        $response = [
            "result" => "error", // 実行結果を格納する(success or error) ※成功時にsuccessに書き換える
            "errCode" => null, // エラーコードがある場合、格納する
            "errMsg" => null, // エラーメッセージがある場合、格納する
            "list" => [],
        ];
        
        // データベース接続の設定
        if(!$response["errMsg"]){
        $host = "localhost";      // 接続するホスト名を指定します。　           例：localhost、DBサーバーアドレス(xxxxxx.db.xxxxx.ne.jp みたいな感じ) etc..
        $user = "";       // 接続するユーザー名を指定します。           例：root、dbuser(自作したユーザー) etc..
        $password = "";   // 接続するユーザーのパスワードを指定します。
        $database = ""; // 接続するデーターベース名を指定します。　　　例：studb、whisperdb etc..
        
        // PDOオブジェクトの作成
        $dsn = "mysql:host={$host};dbname={$database};charset=utf8mb4"; // 接続情報作成 ※dsn = データソース名(Data Source Name)
        $options = [
            PDO::ATTR_ERRMODE => PDO::ERRMODE_EXCEPTION, // クエリ実行時のエラーや接続エラーが発生した場合、例外がスローされるよう指定
            PDO::ATTR_DEFAULT_FETCH_MODE => PDO::FETCH_ASSOC, // 取得した結果を連想配列として取得するフェッチモードの指定
            PDO::ATTR_EMULATE_PREPARES => false, // プリペアドステートメントをエミュレートしないように設定。これによりSQLインジェクション攻撃からの保護が強化されます。
        ];
        try {
            $pdo = new PDO($dsn, $user, $password, $options);  // PDOオブジェクト作成
        } catch (PDOException $e) {
            // エラー処理のPHPファイルにエラーコードを渡す。
            
            throw new PDOException($e->getMessage(), (int) $e->getCode());
            exit;
        }
    }

    
 
        
