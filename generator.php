<?php

/**
 * @param $text
 * @return string
 */
function mb_ucfirst($text)
{
	return mb_strtoupper(mb_substr($text, 0, 1)) . mb_substr($text, 1);
}

/**
 * @param $text
 * @return string
 */
function strtolow($text)
{
	return mb_strtolower(mb_substr($text, 0, 1)) . mb_substr($text, 1);
}

/**
 * @param $text
 * @return string
 */
function generate($text): string
{
	$minWord = 10;
	$maxWord = 30;
	$cntSentence = 50;
	$valueText = [];
	$answerSentence = [];

	preg_match_all('/\[(.*)\]/Usi', $text, $matchesKey);
	$result = array_values(array_unique($matchesKey[1]));

	$matchesValue = explode(' ', $text);

	foreach ($matchesValue as $key => $value) {
		if(!preg_match('/\[(.*)\]/s', $value)) {
			$valueText[] = ['key' => trim($value), 'value' => trim($matchesValue[$key+1])];
		}
	}

	$lenSentence = rand($minWord, $maxWord);

	for ($i = 0; $i < $cntSentence; ++$i) {

		$beginWord = $result[rand(0, count($result)-1)];
		$cnt = 0;
		$answer = '';

		if (strpos($beginWord, '|')) {
			$beginWord = explode('|', $beginWord);
			$beginWord = trim($beginWord[rand(0, count($beginWord)-1)]);
		}

		$answer .= mb_ucfirst($beginWord);
		$searchValue = $answer;

		while (true) {

			foreach ($valueText as $value) {

				if($value['key'] == strtolow($searchValue)) {

					$searchValue = str_replace('[', '', trim($value['value']));
					$searchValue = str_replace(']', '', $searchValue);

					if (strpos($searchValue, '|')) {
						$needText = explode('|', $searchValue);
						$searchValue = trim($needText[rand(0, count($needText)-1)]);
					}

					$answer .= ' ' . $searchValue;
					break;
				}
			}

			if ($lenSentence <= $cnt) {
				$answerSentence[] = $answer .= '. ';
				break;
			}

			++$cnt;
		}
	}

	return implode('<br>', $answerSentence);
}


$text = 'из-за [леса|гор] леса [из-за] гор [едет] едет [дедушка|папочка] дедушка [егор] папочка [гор] егор [сам] сам [на|умер|сыграл-в-ящик] обосрался [на] умер [на] на [лошадке|коровке|телятках|козлятках] лошадке [жена] жена [на] коровке [дети] дети [на] телятках [внуки] внуки [на]';

echo generate($text);