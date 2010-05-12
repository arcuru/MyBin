<?
class Query {
	var $db;
	var $dbname;
	var $dbreturn;
	#constructor, allows function overloading as shown
	function Query($username="patty",$pwd="sqlpasswd",$dbnm="patty_library"){
		$this->db=mysql_connect("localhost",$username,$pwd);
		$this->dbname=$dbnm;
	}
	
	function execute($str) {
		$this->dbreturn=mysql_query($str);
	}
	
	function selectDatabase() {
		if( false==mysql_select_db($this->dbname,$this->db) ) {
			echo "Connection error";
			echo mysql_error();
			exit;
		}
	}
	
	function get() {
		$arr=mysql_fetch_array($this->dbreturn);
		if (!$arr)
			return false;
		foreach($arr as $key=>$value) {
			$this->$key=$value;
		}
		return true;
	}
}
?>
