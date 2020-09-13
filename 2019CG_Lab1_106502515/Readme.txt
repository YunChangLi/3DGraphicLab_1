106502515 陳亮宇 

(一) 自訂義function : 

    init : 

        1. 設定視窗背景顏色
        2. 設定正交投影的XY座標
        3. 設定點的大小
        4. 設定點的顏色

    setpixel : 

        1. 畫點

    storePoint : 

        1. 存點
 
    lineAlgorithm : 
   
        1. 畫線

    circleAlgorithm : 
   
        1. 畫圓
 
    MyMouse : 
  
        1. 點擊事件
        2. 獲得滑鼠點擊座標
        3. 實作 畫點、畫線、畫多邊形、畫圓

    recover : 
      
        1. 恢復所有被清除的點


(二) 按鍵事件

        按下 c 鍵  => 清除所有視窗上的點
        按下 r 鍵  => 恢復所有被清除的點
        按下 d 鍵  => 畫點
        按下 l 鍵  => 畫線
        按下 p 鍵  => 畫多邊形
        按下 o 鍵  => 畫圓
        按下 q 鍵  => 結束程式

(三) 避免 按鍵衝突 => 設立 caseCode
     
        caseCode = "00"  => 清除、恢復、結束程式的功能
        caseCode = "01"  => 畫點
        caseCode = "10"  => 畫線
        caseCode = "11"  => 畫多邊形
        caseCode = "22"  => 畫圓

(四) 重要變數及變數型別

        struct point => 從座標 x , y
        vector<point> list => 存所有畫過的點
        int lineCounter => 分辨起始點和終點
        int polygonCounter => 分辨是否為起始點
        point polygonBegin => 存多邊形起始點
        point circleCenter => 存圓心

(五) 操作手法注意
        
        做不同的事件都必須切換按鍵。
