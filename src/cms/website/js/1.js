1��������֤��
1.1 ����
/^(-|+)?d+$/����������Ϊ��
/^[-+]?d*$/ ����Ϊ��
1.2 ����0������ �����ڴ�����ID����֤)
/^d+$/
1.3 ����������֤
/^-d+$/
1.4 �������ܴ���iMax
����������������д����
1.5 ��������С��iMin
����������������д����
2��ʱ����
2.1 ��ʱ�䣬���� (13:04:06)
��������
function isTime(str)
{
var a = str.match(/^(d{1,2})(:)?(d{1,2})(d{1,2})$/);
if (a == null) {alert(������Ĳ�������ʱ���ʽ��); return false;}
if (a[1]>24 || a[3]>60 || a[4]>60)
{
alert("ʱ���ʽ����");
return false
}
return true;
}


2.2 �����ڣ����� (2003-12-05)
��������
function strDateTime(str)
{
var r = str.match(/^(d{1,4})(-|/)(d{1,2})(d{1,2})$/);
if(r==null)return false;
var d= new Date(r[1], r[3]-1, r[4]);
return (d.getFullYear()==r[1]&&(d.getMonth()+1)==r[3]&&d.getDate()==r[4]);
}

2.3 ��ʱ�䣬���� (2003-12-05 13:04:06)
��������
function strDateTime(str)
{
var reg = /^(d{1,4})(-|/)(d{1,2})(d{1,2}) (d{1,2}):(d{1,2}):(d{1,2})$/;
var r = str.match(reg);
if(r==null)return false;
var d= new Date(r[1], r[3]-1,r[4],r[5],r[6],r[7]);
return (d.getFullYear()==r[1]&&(d.getMonth()+1)==r[3]&&d.getDate()==r[4]&&d.getHours()==r[5]&&d.getMinutes()==r[6]&&d.getSeconds()==r[7]);
}

2.4 ֻ������¡�����(2003-05,����2003-5)

2.5 ֻ��Сʱ�ͷ���,����(12:03)
3������
3.1 ���еı���ֵ������Ϊ��
��������
<input onblur="if(this.value.replace(/^s+|s+$/g,����)==����)alert(������Ϊ��!��)">

3.2 �����ı����ֵ����Ϊ�ա�
3.3 �����ı����ֵ���ܳ���sMaxStrleng
��������
//�����ı����������Ƿ񳬳�
function CheckTextareaLength(val, max_length) {
var str_area=document.forms[0].elements[val].value;
if (str_area!=null&&str_area.length > max_length)
{
alert("�ֶ����ֳ�������������" + max_length +"���ַ������������룡");
document.forms[0].elements[val].focus();
document.forms[0].elements[val].select();
return false;
}
return true;
}

3.4 �����ı����ֵ��������sMixStrleng
3.5 �жϵ�ѡ���Ƿ�ѡ��
��������
function CheckRadio(val,msg1,msg2)
{
var is_radio=document.forms[0].elements[val];
var s_msg1=(msg1==null || msg1=="")? "��ѡ�� radio!":msg1;
var s_msg2=(msg2==null || msg2=="")? "û�п�ѡ�� radio!":msg2;

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
3.6 �жϸ�ѡ���Ƿ�ѡ��.
��������
function CheckCheckbox(val,msg1,msg2)
{
var is_radio=document.forms[0].elements[val];
var s_msg1=(msg1==null || msg1=="")? "��ѡ��CheckBox!":msg1;
var s_msg2=(msg2==null || msg2=="")? "û�п�ѡ��CheckBox!":msg2;

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
3.7 ��ѡ���ȫѡ����ѡ��ȫ��ѡ����ѡ
��������
<form name=hrong>
<input type=checkbox name=All onclick="checkAll(��mm��)">ȫѡ<br/>
<input type=checkbox name=mm onclick="checkItem(��All��)"><br/>
<input type=checkbox name=mm onclick="checkItem(��All��)"><br/>
<input type=checkbox name=mm onclick="checkItem(��All��)"><br/>
<input type=checkbox name=mm onclick="checkItem(��All��)"><br/>
<input type=checkbox name=mm onclick="checkItem(��All��)"><br/><br/>


<input type=checkbox name=All2 onclick="checkAll(��mm2��)">ȫѡ<br/>
<input type=checkbox name=mm2 onclick="checkItem(��All2��)"><br/>
<input type=checkbox name=mm2 onclick="checkItem(��All2��)"><br/>
<input type=checkbox name=mm2 onclick="checkItem(��All2��)"><br/>
<input type=checkbox name=mm2 onclick="checkItem(��All2��)"><br/>
<input type=checkbox name=mm2 onclick="checkItem(��All2��)"><br/>
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

3.8 �ļ��ϴ��������ж��ļ�����
��������
<input type=file onchange="alert(this.value.match(/^(.*)(.)(.{1,8})$/)[3])">

4���ַ���
4.1 �ж��ַ�ȫ����a-Z������A-Z������ĸ���
��������
<input onblur="if(/[^a-zA-Z]/g.test(this.value))alert(���д�)">

4.2 �ж��ַ�����ĸ��������ɡ�
��������
<input onblur="if(/[^0-9a-zA-Z]/g.test(this.value))alert(���д�)">

4.3 �ж��ַ�����ĸ�����֣��»���,������.�ҿ�ͷ��ֻ�����»��ߺ���ĸ
��������
/^([a-zA-z_]{1})([w]*)$/g.test(str)

4.4 �ַ����滻����.Replace();
5���������
5.1 �ж������������
��������
window.navigator.appName

5.2 �ж�ie�İ汾
��������
window.navigator.appVersion

5.3 �жϿͻ��˵ķֱ���
��������
window.screen.height; window.screen.width;

6�������
6.1 email���жϡ�
��������
function ismail(mail)
{
return(new RegExp(/^w+((-w+)|(.w+))*@[A-Za-z0-9]+((.|-)[A-Za-z0-9]+)*.[A-Za-z0-9]+$/).test(mail));
}
6.2 �ֻ��������֤
6.3 ���֤����֤
��������
function isIdCardNo(num)
{
if (isNaN(num)) {alert("����Ĳ������֣�"); return false;}
var len = num.length, re;
if (len == 15)
re = new RegExp(/^(d{6})()?(d{2})(d{2})(d{2})(d{3})$/);
else if (len == 18)
re = new RegExp(/^(d{6})()?(d{4})(d{2})(d{2})(d{3})(d)$/);
else {alert("���������λ�����ԣ�"); return false;}
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
if (!B) {alert("��������֤�� "+ a[0] +" ��������ڲ��ԣ�"); return false;}
}
return true;
}
����һ��
��������
<script>
var aCity={11:"����",12:"���",13:"�ӱ�",14:"ɽ��",15:"���ɹ�",21:"����",22:"����",23:"������ ",31:"�Ϻ�",32:"����",33:"�㽭",34:"����",35:"����",36:"����",37:"ɽ��",41:"����",42:"���� ",43:"����",44:"�㶫",45:"����",46:"����",50:"����",51:"�Ĵ�",52:"����",53:"����",54:"���� ",61:"����",62:"����",63:"�ຣ",64:"����",65:"�½�",71:"̨��",81:"���",82:"����",91:"���� "}

function cidInfo(sId){
var iSum=0
var info=""
if(!/^d{17}(d|x)$/i.test(sId))return false;
sId=sId.replace(/x$/i,"a");
if(aCity[parseInt(sId.substr(0,2))]==null)return "Error:�Ƿ�����";
sBirthday=sId.substr(6,4)+"-"+Number(sId.substr(10,2))+"-"+Number(sId.substr(12,2));
var d=new Date(sBirthday.replace(/-/g,"/"))
if(sBirthday!=(d.getFullYear()+"-"+ (d.getMonth()+1) + "-" + d.getDate()))return "Error:�Ƿ�����";
for(var i = 17;i>=0;i --) iSum += (Math.pow(2,i) % 11) * parseInt(sId.charAt(17 - i),11)
if(iSum%11!=1)return "Error:�Ƿ�֤��";
return aCity[parseInt(sId.substr(0,2))]+","+sBirthday+","+(sId.substr(16,1)%2?"��":"Ů")
}

document.write(cidInfo("380524198002300016"),"<br/>");
document.write(cidInfo("340524198002300019"),"<br/>")
document.write(cidInfo("340524197711111111"),"<br/>")
document.write(cidInfo("34052419800101001x"),"<br/>");
</script>

������������ַУ��
��������
<SCRIPT LANGUAGE="javascript">
function isip(s){
var check=function(v){try{return (v<=255 && v>=0)}catch(x){return false}};
var re=s.split(".")
return (re.length==4)?(check(re[0]) && check(re[1]) && check(re[2]) && check(re[3])):false
}

var s="202.197.78.129";
alert(isip(s))
</SCRIPT>