<html>

<body>
<table width="400" border="1" align="center" cellpadding="0" cellspacing="0">
  <tr>
    <td width="81">标题：</td>
    <td width="313"><?php echo $this->escape($this->title);?></td>
  </tr>
  <tr>
    <td>消息:</td>
    <td><?php echo $this->escape($this->message);?></td>
  </tr>
  <tr>
    <td colspan="2"><?php if( $this->back ) {
			echo "<a href= '".$this->back['url']."'>".$this->escape($this->back['name'])."</a>";}?></td>
  </tr>
</table>


</body>

</html>
