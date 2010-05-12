<?
class Books_Query extends Query {
	function Books_Query() {
		$this->Query();
	}
	
	function queryAllInfo() {
		$this->execute("SELECT * FROM books");
	}
	
	function getBook() {
		return ($this->get());
	}
	
	function findBook($parameter,$id) {
		while ($this->getBook()) {
			if ($this->$id == $parameter) {
				return;
			}
		}
		if ($this->$id != $parameter) {
			echo "ERROR: Need to select a valid book id";
			exit;
		}
	}
	
}
?>
