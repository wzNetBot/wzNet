# Prepare sources three

Merge warzone2100 repository to the project three.

```sh
git remote add -f wz git@github.com:omgbebebe/warzone2100.git
git subtree add --prefix warzone2100 wz master --squash
```

# Build
The `shell.nix` derivation has been prepared for your convenience. You can gather all dependencies and build tools by hand or just type `nix-shell`. It will drop you to preconfigured development environment. Then build it as usual.

```sh
mkdir -p build && cd build
cmake ../ && make
```

## Build Warzone

For build development environment you can use provided `shell.nix` in the Warzone repository.

```sh
pushd warzone2100
./autogen.sh
./configure --prefix=/tmp/wz-dev --with-qtplugins=yes
make -j8 && make install
popd
```
