# building

```bash
mkdir build
cd build
cmake ..
make
make install
sudo ldconfig
```
> ensure that all references to `gr_phil` are gone from `/usr/local/lib`
> The `ldconfig` command sometimes moves symlinks to `.so` files around. Somtimes running `make install` after `sudo ldconfig` fixes things.

## test install

```bash
python -c "import gr_phil; print(gr_phil.symbol_bert(8,(1,1j,-1,-1j)))"
```
