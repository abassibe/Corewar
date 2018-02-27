<?php
include("c_types.php");


////////////////set configs here //////////////
$filename = "./operations.c";


//////////////////end config //////////////////

function print_menu()
{
	echo "Entrée \t- Mettre chaque fonction dans un fichier a son nom,\n";
	echo "\t  et créer un header contenant les prototypes.\n";
	echo "\t  (le fichier d'origine ne sera pas altéré.)\n";
echo "1 \t- Choisir pour chaque fonction le fichier ou elle sera inséré\n";
echo "2 \t- blah blah \n\n";
	echo "Choix :";
	$handle = fopen ("php://stdin","r");
	$line = fgets($handle);
	if(trim($line) == ''){
		return ("default");
		exit;
	}
	else
	{
		return(trim($line));
	}
}

function matching_type($line)
{
	global $types;
	foreach ($types as $key_t => $value_t)
	{
		if ( preg_match ("/^(static )?$value_t.*/",$line))
		{
			if (stripos($line,"static ") !== FALSE)
				return("static ".$value_t);
			return($value_t);
		}
	}
	return(NULL);
}

$brut = file($filename);

$buffer = false;

foreach ($brut as $key => $value)
{
	foreach ($types as $key_t => $value_t)
	{
		if ( preg_match ("/^(static )?$value_t.*/",$value))
		{
			//	echo $value;
			$buffer = true;
			break;
		}
	}

	if ($buffer)
	{
		$func[] = $value;
	}
	else
	{
		$discard[] = $value;
	}

	if (preg_match("/^}\n$/", $value))
	{
		$buffer = false;
		$funcs[] = $func;
		unset($func);
		$func = array();
		//echo "line break @ $key\n";
	}
	//echo $value;
}

echo "discarded :";
print_r($discard);
echo "\n";


$nb = max(array_keys($funcs))+1;
echo "\n$nb fonctions trouvées :\n\n";

//print_r($funcs);
foreach($funcs as $key => $value)
{
	$sub = substr($value[0],strlen(matching_type($value[0])));
	//echo $sub;

	$i = 0;
	while(!ctype_alnum($sub[$i]) && $i < strlen($sub))
	{
		//echo "o";
		$i++;
	}
	$sub = substr($sub, $i );
	$sub = substr($sub, 0, stripos($sub,'('));
	$temp["basename"] = $sub;
	$temp["count"] = count($value);
	$temp["proto"] = str_replace("\n",'',$value[0]).";";
	$meta[$key] = $temp;
	echo " - ".$temp["basename"]."\t (".$temp["count"]." lignes)\n";
	//echo "\n";
	//echo matching_type($value[0]);
}
echo "\n";
//	print_r($funcs);
//	print_r($meta);
function print_files($get)
{
	$i = 0;
	foreach($get as $key => $value)
	{
		echo "$i [".$value["count"]."] - ".$value["filename"]."\t"."\n";	
		$i++;
	}
}

$read = print_menu();
if ($read == "default")
{
	echo  "Entrez le nom du header : ";
	$handle = fopen ("php://stdin","r");
	$line = fgets($handle);
	$line = trim($line);
	$define = str_replace('.','_',strtoupper($line));

	//TO-DO
	//insert header
	file_put_contents($line, "#ifndef $define\n# define $define\n\n", FILE_APPEND);

       foreach($funcs as $key => $value)
       {
	       $finame = $meta[$key]["basename"].".c";

		//TO-DO
		//INSERT HEADER
	       file_put_contents($finame, "#include \"$line\"\n\n", FILE_APPEND);
	       foreach($value as $key_f => $value_f)
	       {
		       file_put_contents($finame, $value_f, FILE_APPEND);
	       }
	       echo " Fonction ".$meta[$key]["basename"].
	       " écrite dans ".$meta[$key]["basename"].".c\n";

		file_put_contents($line, $meta[$key]["proto"]."\n", FILE_APPEND);
	}
	file_put_contents($line, '#endif', FILE_APPEND);
}
elseif($read == '1')
{
	echo  "Entrez le nom du header : ";
	$handle = fopen ("php://stdin","r");
	$line = fgets($handle);
	$line = trim($line);
	$define = str_replace('.','_',strtoupper($line));

	//TO-DO
	//insert header
	file_put_contents($line, "#ifndef $define\n# define $define\n\n", FILE_APPEND);

	$stock = array();
       foreach($funcs as $key => $value)
       {
	       $finame = $meta[$key]["basename"].".c";

		echo(system("clear"));
		echo "\nFichier : $finame\n\n";
		print_files($stock);
	echo "\nEntrer un numero pour mettre la fonction dans un fichier existant,\n"	
	."le caractère '*' pour la mettre dans un fichier .c à son nom\n"
	."ou un nom de fichier pour en créer un nouveau\n";
		echo "Choix :";
		$handle = fopen ("php://stdin","r");
        	$chx = fgets($handle);
        	$chx = trim($chx);
		
		if (is_numeric($chx))
		{
			$good_file = $stock[$chx]["filename"];
			$stock[$chx]["count"]++;
		}
		else if ($chx == '*')
		{
			$stock[] = array("filename" => $finame, "count" => 1);
			$good_file = $finame;
		}
		else
		{
			$stock[] = array("filename" => $chx, "count" => 1);
			$good_file = $chx;

		}
	       	file_put_contents($good_file, "#include \"$line\"\n\n", FILE_APPEND);
		//TO-DO
		//INSERT HEADER
	       foreach($value as $key_f => $value_f)
	       {
		       file_put_contents($good_file, $value_f, FILE_APPEND);
	       }
	       echo " Fonction ".$meta[$key]["basename"].
	       " écrite dans ".$meta[$key]["basename"].".c\n";

		file_put_contents($line, $meta[$key]["proto"]."\n", FILE_APPEND);
	}
	file_put_contents($line, '#endif', FILE_APPEND);
}
//	print_r($brut);
?>
