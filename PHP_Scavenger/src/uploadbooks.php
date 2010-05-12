<?
$db=mysql_connect("localhost","patty","sqlpasswd");
if(false==mysql_select_db("patty_library",$db)){
	echo "Connection error";
	echo mysql_error();
	exit;
}
$success=0;
if ($_REQUEST[submit] == "Submit") {
	$ret=mysql_query("SELECT * FROM books");
	$i=0;
	while ($arr=mysql_fetch_array($ret)) {
		if ( ($_REQUEST[author]==$arr[author]) && ($_REQUEST[title]==$arr[title]) && ($_REQUEST[text]==$arr[text]) ) {
				echo "Book Already Exists";
				exit;
			}
		$i++;
	}
	mysql_query("INSERT INTO books (author, title, text)
		VALUES ('$_REQUEST[author]','$_REQUEST[title]','$_REQUEST[text]')");
	$success=1;
}
?>
<html>
<head><title>Upload Books to the Library</title>
</head>
<body>
<form action="<?=$_SERVER[PHP_SELF]?>" method="post">
<table width="800" align="center">
	<tr>
		<th colspan="2" align="center">
			Enter book Information:
		</th>
	</tr>
	<?if($success==1) {?>
	<tr>
		<td colspan="2" align="center">
			Submission Successful
		</td>
	</tr><?}?>
	<tr>
		<td>Author:</td>
		<td>
			<input type="text" name="author" value="<?if($success==0)$_REQUEST[author]?>">
		</td>
	</tr>
	<tr>
		<td>Title:</td>
		<td>
			<input type="text" name="title" value="<?if($success==0)$_REQUEST[title]?>">
		</td>
	</tr>
	<tr>
		<td>Text:</td>
		<td>
			<textarea wrap="hard" rows="8" cols="50" name="text"><?if($success==0)$_REQUEST[text]?></textarea>
		</td>
	</tr>
	<tr>
		<td colspan="2" align="center">
			<input type="submit" name="submit" value="Submit">
		</td>
	</tr>
	<tr><td>&nbsp</td></tr>
	<tr>
		<td colspan="2" align="center">
			<a href=listbooks>Book List</a>
		</td>
	</tr>
</table>
</body>
</html>
