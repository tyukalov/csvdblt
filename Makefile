 #    This program is free software: you can redistribute it and/or modify
 #    it under the terms of the GNU General Public License as published by
 #    the Free Software Foundation, either version 3 of the License, or
 #    (at your option) any later version.

 #    This program is distributed in the hope that it will be useful,
 #    but WITHOUT ANY WARRANTY; without even the implied warranty of
 #    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 #    GNU General Public License for more details.

 #    You should have received a copy of the GNU General Public License
 #    along with this program.  If not, see <http://www.gnu.org/licenses/>.

 # Igor Tyukalov <tyukalov@bk.ru> 

all:
	gcc -c csvdblt.c
	ar rc libcsvdblt.a csvdblt.o
	rm *.o
	mv libcsvdblt.a ./bin
test: all
	gcc  ./test/test.c ./bin/libcsvdblt.a -o _test
	mv _test ./test/test
debug: 
	gcc -g ./test/test.c csvdblt.c -o test_debug
	mv test_debug ./test
clean:
	rm ./test/test ./test/test_debug ./bin/libcsvdblt.a
