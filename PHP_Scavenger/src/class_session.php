<?
class Session {
	function isLoggedIn() {//returns true if user logged in
		if ( $_SESSION[userid] )
			return 1;
		return 0;
	}
	
	function isRegistered($user) {}
	
	function authenticate($username,$passwd) {
		
	}
}
?>
