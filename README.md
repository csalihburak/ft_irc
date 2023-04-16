<!DOCTYPE html>
<html>
<head>
	<title>IRC Server in C++98</title>
</head>
<body>
	<h1>IRC Server in C++98</h1>
	<p>This project is an implementation of an IRC (Internet Relay Chat) server in C++98. The server is capable of handling multiple clients at the same time and never hangs. Only one poll() function is used for handling all the operations.</p>
	
	<h2>Mandatory Part</h2>
	<p>The following files are required to turn in:</p>
	<ul>
		<li>Makefile</li>
		<li>*.{h, hpp}</li>
		<li>*.cpp</li>
		<li>*.tpp</li>
		<li>*.ipp</li>
		<li>an optional configuration file</li>
	</ul>
	<p>The following targets should be available in Makefile:</p>
	<ul>
		<li>NAME</li>
		<li>all</li>
		<li>clean</li>
		<li>fclean</li>
		<li>re</li>
	</ul>
	<p>The executable is run as follows: ./ircserv &lt;port&gt; &lt;password&gt;</p>
	<ul>
		<li>port: The port number on which your IRC server will be listening to for incoming IRC connections.</li>
		<li>password: The connection password. It will be needed by any IRC client that tries to connect to your server.</li>
	</ul>
	<p>The following external functions are used:</p>
	<ul>
		<li>socket</li>
		<li>close</li>
		<li>setsockopt</li>
		<li>getsockname</li>
		<li>getprotobyname</li>
		<li>gethostbyname</li>
		<li>getaddrinfo</li>
		<li>freeaddrinfo</li>
		<li>bind</li>
		<li>connect</li>
		<li>listen</li>
		<li>accept</li>
		<li>htons</li>
		<li>htonl</li>
		<li>ntohs</li>
		<li>ntohl</li>
		<li>inet_addr</li>
		<li>inet_ntoa</li>
		<li>send</li>
		<li>recv</li>
		<li>signal</li>
		<li>lseek</li>
		<li>fstat</li>
		<li>fcntl</li>
		<li>poll (or equivalent)</li>
	</ul>
	
	<h2>Contributors</h2>
	<ul>
		<li><a href="https://github.com/csalihburak/">Salih Burak Çoşkun</a></li>
		<li><a href="https://github.com/egulerr">Eyüp Güler</a></li>
		<li><a href="https://github.com/Mertflixs/">Mert Alaşahan</a></li>
	</ul>
</body>
</html>
