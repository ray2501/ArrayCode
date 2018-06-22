# ArrayCode
行列查碼程式

目前已可查詢支援到 Unicode 3.1 的輸入法對照表，並且從 v3.1 開始，以 Unicode 3.1 為預設的查碼對照表。

Windows 2000/XP 平台上的特別功能：會使用 IMM API 查詢電腦上的行列三十輸入法與注音輸入法的組字字根，
如果有安裝並且有搜尋到組字字根的話就會列出查詢的結果 （注：行列三十輸入法只會傳回第一筆記錄）。

Library
=====
* wxWidgets 3.0.x or 3.1.x
* C++ Standard Library to store data list
