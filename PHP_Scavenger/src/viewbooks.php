<?
session_start();
include_once("class_session.php");
include_once("class_page.php");
include_once("class_query.php");
include_once("class_books_query.php");
$p=new Page();
$bookq=new Books_Query();
if (preg_match("[0-9]",$_REQUEST[bookid])) {
	echo "ERROR: Need to select a valid book id";
	exit;
};
$bookq->selectDatabase();
$bookq->queryAllInfo();
$bookq->findBook($_REQUEST[bookid],'bookid');
$p->startTemplate();
?>

<table align="center" width="800">
	<tr>
		<th>
			<h1><?= $bookq->author ?></h1>
		</th>
	</tr>
	<tr>
		<th>
			<h2><?= $bookq->title ?></h2>
		</th>
	</tr>
	<tr><td>
			<?=preg_replace("/\n/","<br>",$bookq->text)?>
	</td></tr>
	<tr>
		<td align="center">
			<a href=listbooks>Select New Book</a>
		</td>
	</tr>
</table>
<?$p->close();?>

