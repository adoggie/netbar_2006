1、数字验证内
1.1 整数
/^(-|+)?d+$/　　不可以为空
/^[-+]?d*$/ 可以为空
1.2 大于0的整数 （用于传来的ID的验证)
/^d+$/
1.3 负整数的验证
/^-d+$/
1.4 整数不能大于iMax
根据上面的正则可以写出。
1.5 整数不能小于iMin
根据上面的正则可以写出。
2、时间类
2.1 短时间，形如 (13:04:06)
代码内容
function isTime(str)
{
var a = str.match(/^(d{1,2})(:)?(d{1,2})(d{1,2})$/);
if (a == null) {alert(’输入的参数不是时间格式’); return false;}
if (a[1]>24 || a[3]>60 || a[4]>60)
{
alert("时间格式不对");
return false
}
return true;
}


2.2 短日期，形如 (2003-12-05)
代码内容
function strDateTime(str)
{
var r = str.match(/^(d{1,4})(-|/)(d{1,2})(d{1,2})$/);
if(r==null)return false;
var d= new Date(r[1], r[3]-1, r[4]);
return (d.getFullYear()==r[1]&&(d.getMonth()+1)==r[3]&&d.getDate()==r[4]);
}

2.3 长时间，形如 (2003-12-05 13:04:06)
代码内容
function strDateTime(str)
{
var reg = /^(d{1,4})(-|/)(d{1,2})(d{1,2}) (d{1,2}):(d{1,2}):(d{1,2})$/;
var r = str.match(reg);
if(r==null)return false;
var d= new Date(r[1], r[3]-1,r[4],r[5],r[6],r[7]);
return (d.getFullYear()==r[1]&&(d.getMonth()+1)==r[3]&&d.getDate()==r[4]&&d.getHours()==r[5]&&d.getMinutes()==r[6]&&d.getSeconds()==r[7]);
}

2.4 只有年和月。形如(2003-05,或者2003-5)

2.5 只有小时和分钟,形如(12:03)
3、表单类
3.1 所有的表单的值都不能为空
代码内容
<input onblur="if(this.value.replace(/^s+|s+$/g,’’)==’’)alert(’不能为空!’)">

3.2 多行文本框的值不能为空。
3.3 多行文本框的值不能超过sMaxStrleng
代码内容
//检验文本框中内容是否超长
function CheckTextareaLength(val, max_length) {
var str_area=document.forms[0].elements[val].value;
if (str_area!=null&&str_area.length > max_length)
{
alert("字段文字超长，最多可输入" + max_length +"个字符，请重新输入！");
document.forms[0].elements[val].focus();
document.forms[0].elements[val].select();
return false;
}
return true;
}

3.4 多行文本框的值不能少于sMixStrleng
3.5 判断单选框是否选择。
代码内容
function CheckRadio(val,msg1,msg2)
{
var is_radio=document.forms[0].elements[val];
var s_msg1=(msg1==null || msg1=="")? "请选择 radio!":msg1;
var s_msg2=(msg2==null || msg2=="")? "没有可选的 radio!":msg2;

if(is_radio)
{
if (document.forms[0].elements[val].value != null)
{
if (document.forms[0].elements[val].checked)
{
return true;
}
else
{
alert(s_msg1);
return false;
}
}
else
{
var check_length = document.forms[0].elements[val].length;
var i_count=0
for(var i=0;i<check_length;i++)
{
if (document.forms[0].elements[val](i).checked)
{
i_count=i_count+1;
return true;
}
}
if(i_count==0)
{
alert(s_msg1);
return false;
}
}
}//
else
{
alert(s_msg2);
return false;
}

}
3.6 判断复选框是否选择.
代码内容
function CheckCheckbox(val,msg1,msg2)
{
var is_radio=document.forms[0].elements[val];
var s_msg1=(msg1==null || msg1=="")? "请选择CheckBox!":msg1;
var s_msg2=(msg2==null || msg2=="")? "没有可选的CheckBox!":msg2;

if(is_radio)
{
if (document.forms[0].elements[val].value != null)
{
if (document.forms[0].elements[val].checked)
{
return true;
}
else
{
alert(s_msg1);
return false;
}
}
else
{
var check_length = document.forms[0].elements[val].length;
var i_count=0
for(var i=0;i<check_length;i++)
{
if (document.forms[0].elements[val](i).checked)
{
i_count=i_count+1;
return true;
}
}
if(i_count==0)
{
alert(s_msg1);
return false;
}
}
}//
else
{
alert(s_msg2);
return false;
}

}
3.7 复选框的全选，多选，全不选，反选
代码内容
<form name=hrong>
<input type=checkbox name=All onclick="checkAll(’mm’)">全选<br/>
<input type=checkbox name=mm onclick="checkItem(’All’)"><br/>
<input type=checkbox name=mm onclick="checkItem(’All’)"><br/>
<input type=checkbox name=mm onclick="checkItem(’All’)"><br/>
<input type=checkbox name=mm onclick="checkItem(’All’)"><br/>
<input type=checkbox name=mm onclick="checkItem(’All’)"><br/><br/>


<input type=checkbox name=All2 onclick="checkAll(’mm2’)">全选<br/>
<input type=checkbox name=mm2 onclick="checkItem(’All2’)"><br/>
<input type=checkbox name=mm2 onclick="checkItem(’All2’)"><br/>
<input type=checkbox name=mm2 onclick="checkItem(’All2’)"><br/>
<input type=checkbox name=mm2 onclick="checkItem(’All2’)"><br/>
<input type=checkbox name=mm2 onclick="checkItem(’All2’)"><br/>
</form>
<SCRIPT LANGUAGE="javascript">
function checkAll(str)
{
var a = document.getElementsByName(str);
var n = a.length;
for (var i=0; i<n; i++)
a[i].checked = window.event.srcElement.checked;
}
function checkItem(str)
{
var e = window.event.srcElement;
var all = eval("document.hrong."+ str);
if (e.checked)
{
var a = document.getElementsByName(e.name);
all.checked = true;
for (var i=0; i<a.length; i++)
{
if (!a[i].checked){ all.checked = false; break;}
}
}
else all.checked = false;
}
</SCRIPT>

3.8 文件上传过程中判断文件类型
代码内容
<input type=file onchange="alert(this.value.match(/^(.*)(.)(.{1,8})$/)[3])">

4、字符类
4.1 判断字符全部由a-Z或者是A-Z的字字母组成
代码内容
<input onblur="if(/[^a-zA-Z]/g.test(this.value))alert(’有错’)">

4.2 判断字符由字母和数字组成。
代码内容
<input onblur="if(/[^0-9a-zA-Z]/g.test(this.value))alert(’有错’)">

4.3 判断字符由字母和数字，下划线,点号组成.且开头的只能是下划线和字母
代码内容
/^([a-zA-z_]{1})([w]*)$/g.test(str)

4.4 字符串替换函数.Replace();
5、浏览器类
5.1 判断浏览器的类型
代码内容
window.navigator.appName

5.2 判断ie的版本
代码内容
window.navigator.appVersion

5.3 判断客户端的分辨率
代码内容
window.screen.height; window.screen.width;

6、结合类
6.1 email的判断。
代码内容
function ismail(mail)
{
return(new RegExp(/^w+((-w+)|(.w+))*@[A-Za-z0-9]+((.|-)[A-Za-z0-9]+)*.[A-Za-z0-9]+$/).test(mail));
}
6.2 手机号码的验证
6.3 身份证的验证
代码内容
function isIdCardNo(num)
{
if (isNaN(num)) {alert("输入的不是数字！"); return false;}
var len = num.length, re;
if (len == 15)
re = new RegExp(/^(d{6})()?(d{2})(d{2})(d{2})(d{3})$/);
else if (len == 18)
re = new RegExp(/^(d{6})()?(d{4})(d{2})(d{2})(d{3})(d)$/);
else {alert("输入的数字位数不对！"); return false;}
var a = num.match(re);
if (a != null)
{
if (len==15)
{
var D = new Date("19"+a[3]+"/"+a[4]+"/"+a[5]);
var B = D.getYear()==a[3]&&(D.getMonth()+1)==a[4]&&D.getDate()==a[5];
}
else
{
var D = new Date(a[3]+"/"+a[4]+"/"+a[5]);
var B = D.getFullYear()==a[3]&&(D.getMonth()+1)==a[4]&&D.getDate()==a[5];
}
if (!B) {alert("输入的身份证号 "+ a[0] +" 里出生日期不对！"); return false;}
}
return true;
}
另外一个
代码内容
<script>
var aCity={11:"北京",12:"天津",13:"河北",14:"山西",15:"内蒙古",21:"辽宁",22:"吉林",23:"黑龙江 ",31:"上海",32:"江苏",33:"浙江",34:"安徽",35:"福建",36:"江西",37:"山东",41:"河南",42:"湖北 ",43:"湖南",44:"广东",45:"广西",46:"海南",50:"重庆",51:"四川",52:"贵州",53:"云南",54:"西藏 ",61:"陕西",62:"甘肃",63:"青海",64:"宁夏",65:"新疆",71:"台湾",81:"香港",82:"澳门",91:"国外 "}

function cidInfo(sId){
var iSum=0
var info=""
if(!/^d{17}(d|x)$/i.test(sId))return false;
sId=sId.replace(/x$/i,"a");
if(aCity[parseInt(sId.substr(0,2))]==null)return "Error:非法地区";
sBirthday=sId.substr(6,4)+"-"+Number(sId.substr(10,2))+"-"+Number(sId.substr(12,2));
var d=new Date(sBirthday.replace(/-/g,"/"))
if(sBirthday!=(d.getFullYear()+"-"+ (d.getMonth()+1) + "-" + d.getDate()))return "Error:非法生日";
for(var i = 17;i>=0;i --) iSum += (Math.pow(2,i) % 11) * parseInt(sId.charAt(17 - i),11)
if(iSum%11!=1)return "Error:非法证号";
return aCity[parseInt(sId.substr(0,2))]+","+sBirthday+","+(sId.substr(16,1)%2?"男":"女")
}

document.write(cidInfo("380524198002300016"),"<br/>");
document.write(cidInfo("340524198002300019"),"<br/>")
document.write(cidInfo("340524197711111111"),"<br/>")
document.write(cidInfo("34052419800101001x"),"<br/>");
</script>

６．４　ｉｐ地址校验
代码内容
<SCRIPT LANGUAGE="javascript">
function isip(s){
var check=function(v){try{return (v<=255 && v>=0)}catch(x){return false}};
var re=s.split(".")
return (re.length==4)?(check(re[0]) && check(re[1]) && check(re[2]) && check(re[3])):false
}

var s="202.197.78.129";
alert(isip(s))
</SCRIPT>