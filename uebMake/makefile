a = anziehen
 
Mantel: Pullover Handy Schuhe
	@echo $@ $(a)
	@touch $@

Pullover: Hemd
	@echo $@ $(a)
	@touch $@

Handy: Hose
	@echo $@ $(a)
	@touch $@

Schuhe: Struempfe Hose
	@echo $@ $(a)
	@touch $@

Hose: Hemd Unterhose
	@echo $@ $(a)
	@touch $@

Hemd: Unterhemd
	@echo $@ $(a)
	@touch $@

Unterhemd:
	@echo $@ $(a)
	@touch $@

Unterhose:
	@echo $@ $(a)
	@touch $@

Struempfe:
	@echo $@ $(a)
	@touch $@

Nackt:
	-rm Mantel Pullover Handy Schuhe Hose Hemd Unterhemd Unterhose Struempfe -f
