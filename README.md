# tree_survivor
<pre>
This program uses tree data of different parks of melbourne to calculate their respective
survivability over the years. It also produces relevant stats and maps the initial and final
states of the park (represented as a 100 x 100 grid).

Run in terminal: ./tree_survivor.exe "rainfall amount" < "data file"

Input : TSV file containing tree data.
        1. tree     - Name of tree 
        2. xloc     - X coordinate of the park
        3. yloc     - Y coordinate of the park
        4. liters   - Water required by the tree to survive
        5. rootrad  - Radius of the tree's roots

Output: 1. Total lines of the data file and total water needed annually
        2. Trees which compete for water due to overlapping roots
        3. Initial map of park
        4. Final map of park

Author  - Gazi Mufti Mahmood
Date    - 21/05/2018
</pre>
