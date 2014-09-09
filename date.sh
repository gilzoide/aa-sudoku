#!/bin/bash
# esse é um script para mudar a data dos arquivos-fonte
fonte=*.py
for f in $fonte; do
	eval "sed -i '/^# .*\/.*\/.*/ c\\# `date +%d/%m/%Y`' $f"
done
