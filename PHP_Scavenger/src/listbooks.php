<?
session_start();
include_once("class_session.php");
include_once("class_page.php");
include_once("class_query.php");
include_once("class_books_query.php");
$p=new Page();
$bookq=new Books_Query();
$bookq->selectDatabase();
$bookq->queryAllInfo();
$p->startTemplate('Online Library Book List')
?>
<h1 align="center">Book List</h1>
<table align="center" frame="box" rules="all">
	<tr>
		<th>Author</th>
		<th>Title</th>
	</tr>
		<?while ($bookq->getBook()) {?>
	<tr>
		<td><?=$bookq->author?></td>
		<td>
			<a href="viewbooks?bookid=<?=$bookq->bookid?>">
				<?=$bookq->title?>
			</a>
		</td>
	</tr>
	<?}?>
</table>
<table align="center">
	<tr>
		<td>
			<a href=uploadbooks>Upload A New Book</a>
		</td>
	</tr>
</table>
<?$p->close();?>
