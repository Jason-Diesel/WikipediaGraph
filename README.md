# WikipediaGraphForUpload

<div style="display:flex;">
  <img src="https://github.com/Jason-Diesel/WikipediaGraph/blob/master/GrapgImagesForReadme/Graph1.PNG" alt="Image 1" style="width:49%;">
  <img src="https://github.com/Jason-Diesel/WikipediaGraph/blob/master/GrapgImagesForReadme/Graph2.PNG" alt="Image 2" style="width:49%;">
</div>

<strong>Ooops, the code is not meant to be readeble, but give it a try if you want to</strong><br>

An application that visits an wikipedia site, gets all wikipedia links, and goes trough all of those links.
<br>
This keeps going until there is nothing more to search or the user quits.
<br>
This will also be displayed with a graph in real-time as the search is happening.
<br>

<br>
<strong>The Important files that tackels the problem is: </strong>
<ul>
  <li>WebsiteSearcher</li>
  <li>Graph</li>
  <li>Node</li>
  <li>Renderer</li>
  <li>WikiGraphScene</li>
  <li>NodeQuadTree</li>
  <li>Edge</li>
  <li>WikiNodeVertexShader.vert</li>
  <li>BufferCreator.h</li>
</ul> 
(all in the OpenGL map)
<br><br>
<strong>Controlls</strong><br>
WASD - To move<br>
Scroll - Zoom in and out (might be kinda weird)<br>
F - Start searching wikipedia<br>
Q - Quit searching wikipedia<br>
G - Prints all websites with nr of connections, number of websites searched, number of websites that was found, number of total links that was found.<br>
RightClick - Searches QuadNodeTree for a node at mouse position.<br><br>

<strong>The RightClick will only work in 1920x1080 if not screenSpaceX and screenSpaceY is changed to the size of the current window (My bad here sorry)</strong>
<br>
BTW if you wanna do this the more right way, you should probably download wikipedia https://en.wikipedia.org/wiki/Wikipedia:Database_download. (I haven't done this myself so you can't ask me)

Watch video on the topic
<a href="https://youtu.be/Rvapb45jigU">Link To Youtube video</a>
<br>


