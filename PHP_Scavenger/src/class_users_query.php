class Users_Query extends Query {
	function Users_Query() {
		$this->Query();
	}
	
	function queryAllInfo() {
		$this->execute("SELECT * FROM users");
	}
	
	
}
