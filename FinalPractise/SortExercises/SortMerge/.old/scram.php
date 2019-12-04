<?
$words = file($argv[1]);
for ($i = 0; $i < count($words); $i++) $used[$i] = false;
while (($n = count($words)) > 0) {
	$i = rand(0,count($words)-1);
	echo $words[$i];
	$words[$i] = $words[$n-1];
	unset($words[$n-1]);
}
?>
