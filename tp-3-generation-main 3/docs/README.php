<div id="table-of-contents">
<h2>Table of Contents</h2>
<div id="text-table-of-contents">
<ul>
<li><a href="#orge061a02">1. Introduction</a>
<ul>
<li><a href="#org93b5472">1.1. Download and compiling the library</a></li>
</ul>
</li>
<li><a href="#orgf1fc81a">2. Exercise</a></li>
</ul>
</div>
</div>

<div id="outline-container-orge061a02" class="outline-2">
<h2 id="orge061a02"><span class="section-number-2">1</span> Introduction</h2>
<div class="outline-text-2" id="text-1">
<p>
The goal of the following exercises is to implement a statechart on
the Linux OS. 
</p>

<p>
We will use the <code>sc_minilib</code> library :
</p>

<p>
<a href="https://gitlab-etu.fil.univ-lille1.fr/cle-2021/sc_minilib">https://gitlab-etu.fil.univ-lille1.fr/cle-2021/sc_minilib</a>
</p>
</div>

<div id="outline-container-org93b5472" class="outline-3">
<h3 id="org93b5472"><span class="section-number-3">1.1</span> Download and compiling the library</h3>
<div class="outline-text-3" id="text-1-1">
<p>
Compile and execute the fan example:
</p>
<ul class="org-ul">
<li><p>
Make a directory "build", go inside it, and type cmake and make :
</p>

<div class="org-src-container">
<pre class="src src-sh">mkdir build
<span style="color: #b0c4de;">cd</span> build
cmake ..
make
</pre>
</div></li>

<li><p>
execute the fan example with 
</p>
<div class="org-src-container">
<pre class="src src-sh">./examples/fan/fandemo
</pre>
</div></li>
</ul>
</div>
</div>
</div>

<div id="outline-container-orgf1fc81a" class="outline-2">
<h2 id="orgf1fc81a"><span class="section-number-2">2</span> Exercise</h2>
<div class="outline-text-2" id="text-2">
<p>
The goal of the exercise is to implement the AC system that you
designed in the previous TP with the <code>sc_minilib</code> library.
</p>

<p>
Add a directory <code>examples/ac/</code> to contain the implementation of
the AC controller.
</p>
<ul class="org-ul">
<li>add a <code>CMakeLists.txt</code> to the directory and modify the
<code>examples/CMakeLists.txt</code> accordingly</li>
</ul>

<p>
To simulate the automatic mode, you can change the external
temperature with an appropriate command. For example, you can use
the following commands:
</p>

<ul class="org-ul">
<li>key "*" to turn on/off the system;</li>
<li>key "m" to switch to manual mode and change between "Heating"
and "Cooling";</li>
<li>key "+" and "-" to increase/decrease the desired temperature;</li>
<li>key "t" to enter a value of the current tempeature.</li>
</ul>

<p>
<b>Optional</b>: To better show the results on the screen, you can use
the ncurses library:
</p>

<ul class="org-ul">
<li><a href="https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/helloworld.html">https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/helloworld.html</a></li>
<li><a href="https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/helloworld.html#COMPILECURSES">https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/helloworld.html#COMPILECURSES</a></li>
</ul>

<p>
This allows you to interact with the system in a more natural way
(e.g. by simple keypresses and output at fixed positions in the
screen).
</p>
</div>
</div>
