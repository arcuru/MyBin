<?
class Page {
	function Page($userstatus='dc') {
		if ( $userstatus == "registered" ) {
			if ( !(Session::isLoggedIn()) ) {
				echo 'Not logged in';
				exit;
			}
		}
	}
	
	function startTemplate($title='Online Library') {
		echo '<html><head><title>'.$title.'</title></head><body>';
	}
	
	function close() {
		echo '</body></html>';
	}
}
?>
