#
# Dependencies follow 
./ta.obj ./ta.lst: ./ta.cxx $(CCPLR)/h/bse.h $(CCPLR)/h/bsedev.h \
	$(CCPLR)/h/bsedos.h $(CCPLR)/h/bseerr.h $(CCPLR)/h/bsesub.h \
	$(CCPLR)/h/os2.h $(CCPLR)/h/pm.h $(CCPLR)/h/pmavio.h \
	$(CCPLR)/h/pmbitmap.h $(CCPLR)/h/pmdev.h $(CCPLR)/h/pmerr.h \
	$(CCPLR)/h/pmfont.h $(CCPLR)/h/pmgpi.h $(CCPLR)/h/pmhelp.h \
	$(CCPLR)/h/pmmle.h $(CCPLR)/h/pmord.h $(CCPLR)/h/pmpic.h \
	$(CCPLR)/h/pmshl.h $(CCPLR)/h/pmtypes.h $(CCPLR)/h/pmwin.h \
	$(CCPLR)/h/stddef.h $(CCPLR)/h/stdlib.h $(CCPLR)/h/string.h \
	$(CCPLR)/h/time.h $(COMMON)/H/access.h $(COMMON)/H/alert.h \
	$(COMMON)/H/alertmsg.h $(COMMON)/H/audit.h $(COMMON)/H/chardev.h \
	$(COMMON)/H/config.h $(COMMON)/H/errlog.h $(COMMON)/H/icanon.h \
	$(COMMON)/H/mailslot.h $(COMMON)/H/message.h $(COMMON)/H/ncb.h \
	$(COMMON)/H/net32def.h $(COMMON)/H/netbios.h $(COMMON)/H/netcons.h \
	$(COMMON)/H/neterr.h $(COMMON)/H/netstats.h $(COMMON)/H/profile.h \
	$(COMMON)/H/remutil.h $(COMMON)/H/server.h $(COMMON)/H/service.h \
	$(COMMON)/H/shares.h $(COMMON)/H/use.h $(COMMON)/H/wksta.h \
	$(UI)/common/h/array.hxx $(UI)/common/h/base.hxx \
	$(UI)/common/h/blt.hxx $(UI)/common/h/bltaccel.hxx \
	$(UI)/common/h/bltapp.hxx $(UI)/common/h/bltarrow.hxx \
	$(UI)/common/h/bltatom.hxx $(UI)/common/h/bltbitmp.hxx \
	$(UI)/common/h/bltbutn.hxx $(UI)/common/h/bltcc.hxx \
	$(UI)/common/h/bltclwin.hxx $(UI)/common/h/bltcolh.hxx \
	$(UI)/common/h/bltcons.h $(UI)/common/h/bltctlvl.hxx \
	$(UI)/common/h/bltctrl.hxx $(UI)/common/h/bltcurs.hxx \
	$(UI)/common/h/bltdc.hxx $(UI)/common/h/bltdisph.hxx \
	$(UI)/common/h/bltdlg.hxx $(UI)/common/h/bltedit.hxx \
	$(UI)/common/h/bltevent.hxx $(UI)/common/h/bltfont.hxx \
	$(UI)/common/h/bltfunc.hxx $(UI)/common/h/bltglob.hxx \
	$(UI)/common/h/bltgroup.hxx $(UI)/common/h/bltinit.hxx \
	$(UI)/common/h/bltlb.hxx $(UI)/common/h/bltlc.hxx \
	$(UI)/common/h/bltmain.hxx $(UI)/common/h/bltmisc.hxx \
	$(UI)/common/h/bltmitem.hxx $(UI)/common/h/bltmsgp.hxx \
	$(UI)/common/h/bltpump.hxx $(UI)/common/h/bltrc.h \
	$(UI)/common/h/bltrect.hxx $(UI)/common/h/bltsb.hxx \
	$(UI)/common/h/bltsetbx.hxx $(UI)/common/h/bltsi.hxx \
	$(UI)/common/h/bltspobj.hxx $(UI)/common/h/bltsslt.hxx \
	$(UI)/common/h/bltssn.hxx $(UI)/common/h/bltssnv.hxx \
	$(UI)/common/h/bltsss.hxx $(UI)/common/h/blttd.hxx \
	$(UI)/common/h/blttm.hxx $(UI)/common/h/bltwin.hxx \
	$(UI)/common/h/ctime.hxx $(UI)/common/h/dlist.hxx \
	$(UI)/common/h/heap.hxx $(UI)/common/h/intlprof.hxx \
	$(UI)/common/h/lmui.hxx $(UI)/common/h/lmuitype.h \
	$(UI)/common/h/mnet32.h $(UI)/common/h/mnettype.h \
	$(UI)/common/h/slist.hxx $(UI)/common/h/string.hxx \
	$(UI)/common/h/strlst.hxx $(UI)/common/h/uiassert.hxx \
	$(UI)/common/h/uibuffer.hxx $(UI)/common/hack/dos/dos.h \
	$(UI)/common/hack/dos/netlib.h $(UI)/common/hack/dos/pwin.h \
	$(UI)/common/hack/dos/pwin16.h $(UI)/common/hack/dos/pwintype.h \
	$(UI)/common/hack/dos/windows.h $(UI)/common/hack/os2def.h ./ta.h \
	./ta.hxx

./et.obj ./et.lst: ./et.cxx $(CCPLR)/h/bse.h $(CCPLR)/h/bsedev.h \
	$(CCPLR)/h/bsedos.h $(CCPLR)/h/bseerr.h $(CCPLR)/h/bsesub.h \
	$(CCPLR)/h/os2.h $(CCPLR)/h/pm.h $(CCPLR)/h/pmavio.h \
	$(CCPLR)/h/pmbitmap.h $(CCPLR)/h/pmdev.h $(CCPLR)/h/pmerr.h \
	$(CCPLR)/h/pmfont.h $(CCPLR)/h/pmgpi.h $(CCPLR)/h/pmhelp.h \
	$(CCPLR)/h/pmmle.h $(CCPLR)/h/pmord.h $(CCPLR)/h/pmpic.h \
	$(CCPLR)/h/pmshl.h $(CCPLR)/h/pmtypes.h $(CCPLR)/h/pmwin.h \
	$(CCPLR)/h/stddef.h $(CCPLR)/h/stdlib.h $(CCPLR)/h/time.h \
	$(COMMON)/H/access.h $(COMMON)/H/alert.h $(COMMON)/H/alertmsg.h \
	$(COMMON)/H/audit.h $(COMMON)/H/chardev.h $(COMMON)/H/config.h \
	$(COMMON)/H/errlog.h $(COMMON)/H/icanon.h $(COMMON)/H/lan.h \
	$(COMMON)/H/mailslot.h $(COMMON)/H/message.h $(COMMON)/H/ncb.h \
	$(COMMON)/H/net32def.h $(COMMON)/H/netbios.h $(COMMON)/H/netcons.h \
	$(COMMON)/H/neterr.h $(COMMON)/H/netstats.h $(COMMON)/H/nmpipe.h \
	$(COMMON)/H/profile.h $(COMMON)/H/remutil.h $(COMMON)/H/server.h \
	$(COMMON)/H/service.h $(COMMON)/H/shares.h $(COMMON)/H/use.h \
	$(COMMON)/H/wksta.h $(UI)/common/h/array.hxx $(UI)/common/h/base.hxx \
	$(UI)/common/h/blt.hxx $(UI)/common/h/bltaccel.hxx \
	$(UI)/common/h/bltapp.hxx $(UI)/common/h/bltarrow.hxx \
	$(UI)/common/h/bltatom.hxx $(UI)/common/h/bltbitmp.hxx \
	$(UI)/common/h/bltbutn.hxx $(UI)/common/h/bltcc.hxx \
	$(UI)/common/h/bltclwin.hxx $(UI)/common/h/bltcolh.hxx \
	$(UI)/common/h/bltcons.h $(UI)/common/h/bltctlvl.hxx \
	$(UI)/common/h/bltctrl.hxx $(UI)/common/h/bltcurs.hxx \
	$(UI)/common/h/bltdc.hxx $(UI)/common/h/bltdisph.hxx \
	$(UI)/common/h/bltdlg.hxx $(UI)/common/h/bltedit.hxx \
	$(UI)/common/h/bltevent.hxx $(UI)/common/h/bltfont.hxx \
	$(UI)/common/h/bltfunc.hxx $(UI)/common/h/bltglob.hxx \
	$(UI)/common/h/bltgroup.hxx $(UI)/common/h/bltinit.hxx \
	$(UI)/common/h/bltlb.hxx $(UI)/common/h/bltlc.hxx \
	$(UI)/common/h/bltmain.hxx $(UI)/common/h/bltmisc.hxx \
	$(UI)/common/h/bltmitem.hxx $(UI)/common/h/bltmsgp.hxx \
	$(UI)/common/h/bltpump.hxx $(UI)/common/h/bltrc.h \
	$(UI)/common/h/bltrect.hxx $(UI)/common/h/bltsb.hxx \
	$(UI)/common/h/bltsetbx.hxx $(UI)/common/h/bltsi.hxx \
	$(UI)/common/h/bltspobj.hxx $(UI)/common/h/bltsslt.hxx \
	$(UI)/common/h/bltssn.hxx $(UI)/common/h/bltssnv.hxx \
	$(UI)/common/h/bltsss.hxx $(UI)/common/h/blttd.hxx \
	$(UI)/common/h/blttm.hxx $(UI)/common/h/bltwin.hxx \
	$(UI)/common/h/ctime.hxx $(UI)/common/h/dlist.hxx \
	$(UI)/common/h/heap.hxx $(UI)/common/h/intlprof.hxx \
	$(UI)/common/h/lmui.hxx $(UI)/common/h/lmuitype.h \
	$(UI)/common/h/mnet32.h $(UI)/common/h/mnettype.h \
	$(UI)/common/h/slist.hxx $(UI)/common/h/string.hxx \
	$(UI)/common/h/strlst.hxx $(UI)/common/h/uiassert.hxx \
	$(UI)/common/h/uibuffer.hxx $(UI)/common/h/uitrace.hxx \
	$(UI)/common/hack/dos/dos.h $(UI)/common/hack/dos/netlib.h \
	$(UI)/common/hack/dos/pwin.h $(UI)/common/hack/dos/pwin16.h \
	$(UI)/common/hack/dos/pwintype.h $(UI)/common/hack/dos/windows.h \
	$(UI)/common/hack/os2def.h ./ta.h ./ta.hxx ./tester.hxx

./curstest.obj ./curstest.lst: ./curstest.cxx $(CCPLR)/h/bse.h \
	$(CCPLR)/h/bsedev.h $(CCPLR)/h/bsedos.h $(CCPLR)/h/bseerr.h \
	$(CCPLR)/h/bsesub.h $(CCPLR)/h/os2.h $(CCPLR)/h/pm.h \
	$(CCPLR)/h/pmavio.h $(CCPLR)/h/pmbitmap.h $(CCPLR)/h/pmdev.h \
	$(CCPLR)/h/pmerr.h $(CCPLR)/h/pmfont.h $(CCPLR)/h/pmgpi.h \
	$(CCPLR)/h/pmhelp.h $(CCPLR)/h/pmmle.h $(CCPLR)/h/pmord.h \
	$(CCPLR)/h/pmpic.h $(CCPLR)/h/pmshl.h $(CCPLR)/h/pmtypes.h \
	$(CCPLR)/h/pmwin.h $(CCPLR)/h/search.h $(CCPLR)/h/stddef.h \
	$(CCPLR)/h/stdlib.h $(CCPLR)/h/time.h $(COMMON)/H/access.h \
	$(COMMON)/H/alert.h $(COMMON)/H/alertmsg.h $(COMMON)/H/audit.h \
	$(COMMON)/H/chardev.h $(COMMON)/H/config.h $(COMMON)/H/errlog.h \
	$(COMMON)/H/icanon.h $(COMMON)/H/mailslot.h $(COMMON)/H/message.h \
	$(COMMON)/H/ncb.h $(COMMON)/H/net32def.h $(COMMON)/H/netbios.h \
	$(COMMON)/H/netcons.h $(COMMON)/H/neterr.h $(COMMON)/H/netstats.h \
	$(COMMON)/H/profile.h $(COMMON)/H/remutil.h $(COMMON)/H/server.h \
	$(COMMON)/H/service.h $(COMMON)/H/shares.h $(COMMON)/H/use.h \
	$(COMMON)/H/wksta.h $(UI)/common/h/array.hxx $(UI)/common/h/base.hxx \
	$(UI)/common/h/blt.hxx $(UI)/common/h/bltaccel.hxx \
	$(UI)/common/h/bltapp.hxx $(UI)/common/h/bltarrow.hxx \
	$(UI)/common/h/bltatom.hxx $(UI)/common/h/bltbitmp.hxx \
	$(UI)/common/h/bltbutn.hxx $(UI)/common/h/bltcc.hxx \
	$(UI)/common/h/bltclwin.hxx $(UI)/common/h/bltcolh.hxx \
	$(UI)/common/h/bltcons.h $(UI)/common/h/bltctlvl.hxx \
	$(UI)/common/h/bltctrl.hxx $(UI)/common/h/bltcurs.hxx \
	$(UI)/common/h/bltdc.hxx $(UI)/common/h/bltdisph.hxx \
	$(UI)/common/h/bltdlg.hxx $(UI)/common/h/bltedit.hxx \
	$(UI)/common/h/bltevent.hxx $(UI)/common/h/bltfont.hxx \
	$(UI)/common/h/bltfunc.hxx $(UI)/common/h/bltglob.hxx \
	$(UI)/common/h/bltgroup.hxx $(UI)/common/h/bltinit.hxx \
	$(UI)/common/h/bltlb.hxx $(UI)/common/h/bltlc.hxx \
	$(UI)/common/h/bltmain.hxx $(UI)/common/h/bltmisc.hxx \
	$(UI)/common/h/bltmitem.hxx $(UI)/common/h/bltmsgp.hxx \
	$(UI)/common/h/bltpump.hxx $(UI)/common/h/bltrc.h \
	$(UI)/common/h/bltrect.hxx $(UI)/common/h/bltsb.hxx \
	$(UI)/common/h/bltsetbx.hxx $(UI)/common/h/bltsi.hxx \
	$(UI)/common/h/bltspobj.hxx $(UI)/common/h/bltsslt.hxx \
	$(UI)/common/h/bltssn.hxx $(UI)/common/h/bltssnv.hxx \
	$(UI)/common/h/bltsss.hxx $(UI)/common/h/blttd.hxx \
	$(UI)/common/h/blttm.hxx $(UI)/common/h/bltwin.hxx \
	$(UI)/common/h/ctime.hxx $(UI)/common/h/dlist.hxx \
	$(UI)/common/h/heap.hxx $(UI)/common/h/intlprof.hxx \
	$(UI)/common/h/lmui.hxx $(UI)/common/h/lmuitype.h \
	$(UI)/common/h/mnet32.h $(UI)/common/h/mnettype.h \
	$(UI)/common/h/slist.hxx $(UI)/common/h/string.hxx \
	$(UI)/common/h/strlst.hxx $(UI)/common/h/uiassert.hxx \
	$(UI)/common/h/uibuffer.hxx $(UI)/common/h/uitrace.hxx \
	$(UI)/common/hack/dos/netlib.h $(UI)/common/hack/dos/pwin.h \
	$(UI)/common/hack/dos/pwin16.h $(UI)/common/hack/dos/pwintype.h \
	$(UI)/common/hack/dos/windows.h $(UI)/common/hack/os2def.h

./dialog.obj ./dialog.lst: ./dialog.cxx $(CCPLR)/h/bse.h \
	$(CCPLR)/h/bsedev.h $(CCPLR)/h/bsedos.h $(CCPLR)/h/bseerr.h \
	$(CCPLR)/h/bsesub.h $(CCPLR)/h/os2.h $(CCPLR)/h/pm.h \
	$(CCPLR)/h/pmavio.h $(CCPLR)/h/pmbitmap.h $(CCPLR)/h/pmdev.h \
	$(CCPLR)/h/pmerr.h $(CCPLR)/h/pmfont.h $(CCPLR)/h/pmgpi.h \
	$(CCPLR)/h/pmhelp.h $(CCPLR)/h/pmmle.h $(CCPLR)/h/pmord.h \
	$(CCPLR)/h/pmpic.h $(CCPLR)/h/pmshl.h $(CCPLR)/h/pmtypes.h \
	$(CCPLR)/h/pmwin.h $(CCPLR)/h/stddef.h $(CCPLR)/h/stdlib.h \
	$(CCPLR)/h/time.h $(COMMON)/H/access.h $(COMMON)/H/alert.h \
	$(COMMON)/H/alertmsg.h $(COMMON)/H/audit.h $(COMMON)/H/chardev.h \
	$(COMMON)/H/config.h $(COMMON)/H/errlog.h $(COMMON)/H/icanon.h \
	$(COMMON)/H/lan.h $(COMMON)/H/mailslot.h $(COMMON)/H/message.h \
	$(COMMON)/H/ncb.h $(COMMON)/H/net32def.h $(COMMON)/H/netbios.h \
	$(COMMON)/H/netcons.h $(COMMON)/H/neterr.h $(COMMON)/H/netstats.h \
	$(COMMON)/H/nmpipe.h $(COMMON)/H/profile.h $(COMMON)/H/remutil.h \
	$(COMMON)/H/server.h $(COMMON)/H/service.h $(COMMON)/H/shares.h \
	$(COMMON)/H/use.h $(COMMON)/H/wksta.h $(UI)/common/h/array.hxx \
	$(UI)/common/h/base.hxx $(UI)/common/h/blt.hxx \
	$(UI)/common/h/bltaccel.hxx $(UI)/common/h/bltapp.hxx \
	$(UI)/common/h/bltarrow.hxx $(UI)/common/h/bltatom.hxx \
	$(UI)/common/h/bltbitmp.hxx $(UI)/common/h/bltbutn.hxx \
	$(UI)/common/h/bltcc.hxx $(UI)/common/h/bltclwin.hxx \
	$(UI)/common/h/bltcolh.hxx $(UI)/common/h/bltcons.h \
	$(UI)/common/h/bltctlvl.hxx $(UI)/common/h/bltctrl.hxx \
	$(UI)/common/h/bltcurs.hxx $(UI)/common/h/bltdc.hxx \
	$(UI)/common/h/bltdisph.hxx $(UI)/common/h/bltdlg.hxx \
	$(UI)/common/h/bltedit.hxx $(UI)/common/h/bltevent.hxx \
	$(UI)/common/h/bltfont.hxx $(UI)/common/h/bltfunc.hxx \
	$(UI)/common/h/bltglob.hxx $(UI)/common/h/bltgroup.hxx \
	$(UI)/common/h/bltinit.hxx $(UI)/common/h/bltlb.hxx \
	$(UI)/common/h/bltlc.hxx $(UI)/common/h/bltmain.hxx \
	$(UI)/common/h/bltmisc.hxx $(UI)/common/h/bltmitem.hxx \
	$(UI)/common/h/bltmsgp.hxx $(UI)/common/h/bltpump.hxx \
	$(UI)/common/h/bltrc.h $(UI)/common/h/bltrect.hxx \
	$(UI)/common/h/bltsb.hxx $(UI)/common/h/bltsetbx.hxx \
	$(UI)/common/h/bltsi.hxx $(UI)/common/h/bltspobj.hxx \
	$(UI)/common/h/bltsslt.hxx $(UI)/common/h/bltssn.hxx \
	$(UI)/common/h/bltssnv.hxx $(UI)/common/h/bltsss.hxx \
	$(UI)/common/h/blttd.hxx $(UI)/common/h/blttm.hxx \
	$(UI)/common/h/bltwin.hxx $(UI)/common/h/ctime.hxx \
	$(UI)/common/h/dlist.hxx $(UI)/common/h/heap.hxx \
	$(UI)/common/h/intlprof.hxx $(UI)/common/h/lmui.hxx \
	$(UI)/common/h/lmuitype.h $(UI)/common/h/mnet32.h \
	$(UI)/common/h/mnettype.h $(UI)/common/h/slist.hxx \
	$(UI)/common/h/string.hxx $(UI)/common/h/strlst.hxx \
	$(UI)/common/h/uiassert.hxx $(UI)/common/h/uibuffer.hxx \
	$(UI)/common/h/uitrace.hxx $(UI)/common/hack/dos/dos.h \
	$(UI)/common/hack/dos/netlib.h $(UI)/common/hack/dos/pwin.h \
	$(UI)/common/hack/dos/pwin16.h $(UI)/common/hack/dos/pwintype.h \
	$(UI)/common/hack/dos/windows.h $(UI)/common/hack/os2def.h ./ta.h \
	./ta.hxx ./tester.hxx

./checkbox.obj ./checkbox.lst: ./checkbox.cxx $(CCPLR)/h/bse.h \
	$(CCPLR)/h/bsedev.h $(CCPLR)/h/bsedos.h $(CCPLR)/h/bseerr.h \
	$(CCPLR)/h/bsesub.h $(CCPLR)/h/os2.h $(CCPLR)/h/pm.h \
	$(CCPLR)/h/pmavio.h $(CCPLR)/h/pmbitmap.h $(CCPLR)/h/pmdev.h \
	$(CCPLR)/h/pmerr.h $(CCPLR)/h/pmfont.h $(CCPLR)/h/pmgpi.h \
	$(CCPLR)/h/pmhelp.h $(CCPLR)/h/pmmle.h $(CCPLR)/h/pmord.h \
	$(CCPLR)/h/pmpic.h $(CCPLR)/h/pmshl.h $(CCPLR)/h/pmtypes.h \
	$(CCPLR)/h/pmwin.h $(CCPLR)/h/stddef.h $(CCPLR)/h/stdlib.h \
	$(CCPLR)/h/time.h $(COMMON)/H/access.h $(COMMON)/H/alert.h \
	$(COMMON)/H/alertmsg.h $(COMMON)/H/audit.h $(COMMON)/H/chardev.h \
	$(COMMON)/H/config.h $(COMMON)/H/errlog.h $(COMMON)/H/icanon.h \
	$(COMMON)/H/lan.h $(COMMON)/H/mailslot.h $(COMMON)/H/message.h \
	$(COMMON)/H/ncb.h $(COMMON)/H/net32def.h $(COMMON)/H/netbios.h \
	$(COMMON)/H/netcons.h $(COMMON)/H/neterr.h $(COMMON)/H/netstats.h \
	$(COMMON)/H/nmpipe.h $(COMMON)/H/profile.h $(COMMON)/H/remutil.h \
	$(COMMON)/H/server.h $(COMMON)/H/service.h $(COMMON)/H/shares.h \
	$(COMMON)/H/use.h $(COMMON)/H/wksta.h $(UI)/common/h/array.hxx \
	$(UI)/common/h/base.hxx $(UI)/common/h/blt.hxx \
	$(UI)/common/h/bltaccel.hxx $(UI)/common/h/bltapp.hxx \
	$(UI)/common/h/bltarrow.hxx $(UI)/common/h/bltatom.hxx \
	$(UI)/common/h/bltbitmp.hxx $(UI)/common/h/bltbutn.hxx \
	$(UI)/common/h/bltcc.hxx $(UI)/common/h/bltclwin.hxx \
	$(UI)/common/h/bltcolh.hxx $(UI)/common/h/bltcons.h \
	$(UI)/common/h/bltctlvl.hxx $(UI)/common/h/bltctrl.hxx \
	$(UI)/common/h/bltcurs.hxx $(UI)/common/h/bltdc.hxx \
	$(UI)/common/h/bltdisph.hxx $(UI)/common/h/bltdlg.hxx \
	$(UI)/common/h/bltedit.hxx $(UI)/common/h/bltevent.hxx \
	$(UI)/common/h/bltfont.hxx $(UI)/common/h/bltfunc.hxx \
	$(UI)/common/h/bltglob.hxx $(UI)/common/h/bltgroup.hxx \
	$(UI)/common/h/bltinit.hxx $(UI)/common/h/bltlb.hxx \
	$(UI)/common/h/bltlc.hxx $(UI)/common/h/bltmain.hxx \
	$(UI)/common/h/bltmisc.hxx $(UI)/common/h/bltmitem.hxx \
	$(UI)/common/h/bltmsgp.hxx $(UI)/common/h/bltpump.hxx \
	$(UI)/common/h/bltrc.h $(UI)/common/h/bltrect.hxx \
	$(UI)/common/h/bltsb.hxx $(UI)/common/h/bltsetbx.hxx \
	$(UI)/common/h/bltsi.hxx $(UI)/common/h/bltspobj.hxx \
	$(UI)/common/h/bltsslt.hxx $(UI)/common/h/bltssn.hxx \
	$(UI)/common/h/bltssnv.hxx $(UI)/common/h/bltsss.hxx \
	$(UI)/common/h/blttd.hxx $(UI)/common/h/blttm.hxx \
	$(UI)/common/h/bltwin.hxx $(UI)/common/h/ctime.hxx \
	$(UI)/common/h/dlist.hxx $(UI)/common/h/heap.hxx \
	$(UI)/common/h/intlprof.hxx $(UI)/common/h/lmui.hxx \
	$(UI)/common/h/lmuitype.h $(UI)/common/h/mnet32.h \
	$(UI)/common/h/mnettype.h $(UI)/common/h/slist.hxx \
	$(UI)/common/h/string.hxx $(UI)/common/h/strlst.hxx \
	$(UI)/common/h/uiassert.hxx $(UI)/common/h/uibuffer.hxx \
	$(UI)/common/h/uitrace.hxx $(UI)/common/hack/dos/dos.h \
	$(UI)/common/hack/dos/netlib.h $(UI)/common/hack/dos/pwin.h \
	$(UI)/common/hack/dos/pwin16.h $(UI)/common/hack/dos/pwintype.h \
	$(UI)/common/hack/dos/windows.h $(UI)/common/hack/os2def.h ./ta.h \
	./ta.hxx ./tester.hxx

./domain.obj ./domain.lst: ./domain.cxx $(CCPLR)/h/bse.h \
	$(CCPLR)/h/bsedev.h $(CCPLR)/h/bsedos.h $(CCPLR)/h/bseerr.h \
	$(CCPLR)/h/bsesub.h $(CCPLR)/h/os2.h $(CCPLR)/h/pm.h \
	$(CCPLR)/h/pmavio.h $(CCPLR)/h/pmbitmap.h $(CCPLR)/h/pmdev.h \
	$(CCPLR)/h/pmerr.h $(CCPLR)/h/pmfont.h $(CCPLR)/h/pmgpi.h \
	$(CCPLR)/h/pmhelp.h $(CCPLR)/h/pmmle.h $(CCPLR)/h/pmord.h \
	$(CCPLR)/h/pmpic.h $(CCPLR)/h/pmshl.h $(CCPLR)/h/pmtypes.h \
	$(CCPLR)/h/pmwin.h $(CCPLR)/h/stddef.h $(CCPLR)/h/stdlib.h \
	$(CCPLR)/h/time.h $(COMMON)/H/access.h $(COMMON)/H/alert.h \
	$(COMMON)/H/alertmsg.h $(COMMON)/H/audit.h $(COMMON)/H/chardev.h \
	$(COMMON)/H/config.h $(COMMON)/H/errlog.h $(COMMON)/H/icanon.h \
	$(COMMON)/H/lan.h $(COMMON)/H/mailslot.h $(COMMON)/H/message.h \
	$(COMMON)/H/ncb.h $(COMMON)/H/net32def.h $(COMMON)/H/netbios.h \
	$(COMMON)/H/netcons.h $(COMMON)/H/neterr.h $(COMMON)/H/netstats.h \
	$(COMMON)/H/nmpipe.h $(COMMON)/H/profile.h $(COMMON)/H/remutil.h \
	$(COMMON)/H/server.h $(COMMON)/H/service.h $(COMMON)/H/shares.h \
	$(COMMON)/H/use.h $(COMMON)/H/wksta.h $(UI)/common/h/array.hxx \
	$(UI)/common/h/base.hxx $(UI)/common/h/blt.hxx \
	$(UI)/common/h/bltaccel.hxx $(UI)/common/h/bltapp.hxx \
	$(UI)/common/h/bltarrow.hxx $(UI)/common/h/bltatom.hxx \
	$(UI)/common/h/bltbitmp.hxx $(UI)/common/h/bltbutn.hxx \
	$(UI)/common/h/bltcc.hxx $(UI)/common/h/bltclwin.hxx \
	$(UI)/common/h/bltcolh.hxx $(UI)/common/h/bltcons.h \
	$(UI)/common/h/bltctlvl.hxx $(UI)/common/h/bltctrl.hxx \
	$(UI)/common/h/bltcurs.hxx $(UI)/common/h/bltdc.hxx \
	$(UI)/common/h/bltdisph.hxx $(UI)/common/h/bltdlg.hxx \
	$(UI)/common/h/bltedit.hxx $(UI)/common/h/bltevent.hxx \
	$(UI)/common/h/bltfont.hxx $(UI)/common/h/bltfunc.hxx \
	$(UI)/common/h/bltglob.hxx $(UI)/common/h/bltgroup.hxx \
	$(UI)/common/h/bltinit.hxx $(UI)/common/h/bltlb.hxx \
	$(UI)/common/h/bltlc.hxx $(UI)/common/h/bltmain.hxx \
	$(UI)/common/h/bltmisc.hxx $(UI)/common/h/bltmitem.hxx \
	$(UI)/common/h/bltmsgp.hxx $(UI)/common/h/bltpump.hxx \
	$(UI)/common/h/bltrc.h $(UI)/common/h/bltrect.hxx \
	$(UI)/common/h/bltsb.hxx $(UI)/common/h/bltsetbx.hxx \
	$(UI)/common/h/bltsi.hxx $(UI)/common/h/bltspobj.hxx \
	$(UI)/common/h/bltsslt.hxx $(UI)/common/h/bltssn.hxx \
	$(UI)/common/h/bltssnv.hxx $(UI)/common/h/bltsss.hxx \
	$(UI)/common/h/blttd.hxx $(UI)/common/h/blttm.hxx \
	$(UI)/common/h/bltwin.hxx $(UI)/common/h/ctime.hxx \
	$(UI)/common/h/dlist.hxx $(UI)/common/h/heap.hxx \
	$(UI)/common/h/intlprof.hxx $(UI)/common/h/lmui.hxx \
	$(UI)/common/h/lmuitype.h $(UI)/common/h/mnet32.h \
	$(UI)/common/h/mnettype.h $(UI)/common/h/slist.hxx \
	$(UI)/common/h/string.hxx $(UI)/common/h/strlst.hxx \
	$(UI)/common/h/uiassert.hxx $(UI)/common/h/uibuffer.hxx \
	$(UI)/common/h/uitrace.hxx $(UI)/common/hack/dos/dos.h \
	$(UI)/common/hack/dos/netlib.h $(UI)/common/hack/dos/pwin.h \
	$(UI)/common/hack/dos/pwin16.h $(UI)/common/hack/dos/pwintype.h \
	$(UI)/common/hack/dos/windows.h $(UI)/common/hack/os2def.h ./ta.h \
	./ta.hxx ./tester.hxx

./slb.obj ./slb.lst: ./slb.cxx $(CCPLR)/h/bse.h $(CCPLR)/h/bsedev.h \
	$(CCPLR)/h/bsedos.h $(CCPLR)/h/bseerr.h $(CCPLR)/h/bsesub.h \
	$(CCPLR)/h/os2.h $(CCPLR)/h/pm.h $(CCPLR)/h/pmavio.h \
	$(CCPLR)/h/pmbitmap.h $(CCPLR)/h/pmdev.h $(CCPLR)/h/pmerr.h \
	$(CCPLR)/h/pmfont.h $(CCPLR)/h/pmgpi.h $(CCPLR)/h/pmhelp.h \
	$(CCPLR)/h/pmmle.h $(CCPLR)/h/pmord.h $(CCPLR)/h/pmpic.h \
	$(CCPLR)/h/pmshl.h $(CCPLR)/h/pmtypes.h $(CCPLR)/h/pmwin.h \
	$(CCPLR)/h/stddef.h $(CCPLR)/h/stdlib.h $(CCPLR)/h/time.h \
	$(COMMON)/H/access.h $(COMMON)/H/alert.h $(COMMON)/H/alertmsg.h \
	$(COMMON)/H/audit.h $(COMMON)/H/chardev.h $(COMMON)/H/config.h \
	$(COMMON)/H/errlog.h $(COMMON)/H/icanon.h $(COMMON)/H/lan.h \
	$(COMMON)/H/mailslot.h $(COMMON)/H/message.h $(COMMON)/H/ncb.h \
	$(COMMON)/H/net32def.h $(COMMON)/H/netbios.h $(COMMON)/H/netcons.h \
	$(COMMON)/H/neterr.h $(COMMON)/H/netstats.h $(COMMON)/H/nmpipe.h \
	$(COMMON)/H/profile.h $(COMMON)/H/remutil.h $(COMMON)/H/server.h \
	$(COMMON)/H/service.h $(COMMON)/H/shares.h $(COMMON)/H/use.h \
	$(COMMON)/H/wksta.h $(UI)/common/h/array.hxx $(UI)/common/h/base.hxx \
	$(UI)/common/h/blt.hxx $(UI)/common/h/bltaccel.hxx \
	$(UI)/common/h/bltapp.hxx $(UI)/common/h/bltarrow.hxx \
	$(UI)/common/h/bltatom.hxx $(UI)/common/h/bltbitmp.hxx \
	$(UI)/common/h/bltbutn.hxx $(UI)/common/h/bltcc.hxx \
	$(UI)/common/h/bltclwin.hxx $(UI)/common/h/bltcolh.hxx \
	$(UI)/common/h/bltcons.h $(UI)/common/h/bltctlvl.hxx \
	$(UI)/common/h/bltctrl.hxx $(UI)/common/h/bltcurs.hxx \
	$(UI)/common/h/bltdc.hxx $(UI)/common/h/bltdisph.hxx \
	$(UI)/common/h/bltdlg.hxx $(UI)/common/h/bltedit.hxx \
	$(UI)/common/h/bltevent.hxx $(UI)/common/h/bltfont.hxx \
	$(UI)/common/h/bltfunc.hxx $(UI)/common/h/bltglob.hxx \
	$(UI)/common/h/bltgroup.hxx $(UI)/common/h/bltinit.hxx \
	$(UI)/common/h/bltlb.hxx $(UI)/common/h/bltlc.hxx \
	$(UI)/common/h/bltmain.hxx $(UI)/common/h/bltmisc.hxx \
	$(UI)/common/h/bltmitem.hxx $(UI)/common/h/bltmsgp.hxx \
	$(UI)/common/h/bltpump.hxx $(UI)/common/h/bltrc.h \
	$(UI)/common/h/bltrect.hxx $(UI)/common/h/bltsb.hxx \
	$(UI)/common/h/bltsetbx.hxx $(UI)/common/h/bltsi.hxx \
	$(UI)/common/h/bltspobj.hxx $(UI)/common/h/bltsslt.hxx \
	$(UI)/common/h/bltssn.hxx $(UI)/common/h/bltssnv.hxx \
	$(UI)/common/h/bltsss.hxx $(UI)/common/h/blttd.hxx \
	$(UI)/common/h/blttm.hxx $(UI)/common/h/bltwin.hxx \
	$(UI)/common/h/ctime.hxx $(UI)/common/h/dlist.hxx \
	$(UI)/common/h/heap.hxx $(UI)/common/h/intlprof.hxx \
	$(UI)/common/h/lmui.hxx $(UI)/common/h/lmuitype.h \
	$(UI)/common/h/mnet32.h $(UI)/common/h/mnettype.h \
	$(UI)/common/h/slist.hxx $(UI)/common/h/string.hxx \
	$(UI)/common/h/strlst.hxx $(UI)/common/h/uiassert.hxx \
	$(UI)/common/h/uibuffer.hxx $(UI)/common/h/uitrace.hxx \
	$(UI)/common/hack/dos/dos.h $(UI)/common/hack/dos/netlib.h \
	$(UI)/common/hack/dos/pwin.h $(UI)/common/hack/dos/pwin16.h \
	$(UI)/common/hack/dos/pwintype.h $(UI)/common/hack/dos/windows.h \
	$(UI)/common/hack/os2def.h ./ta.h ./ta.hxx ./tester.hxx

./bitmap.obj ./bitmap.lst: ./bitmap.cxx $(CCPLR)/h/bse.h \
	$(CCPLR)/h/bsedev.h $(CCPLR)/h/bsedos.h $(CCPLR)/h/bseerr.h \
	$(CCPLR)/h/bsesub.h $(CCPLR)/h/os2.h $(CCPLR)/h/pm.h \
	$(CCPLR)/h/pmavio.h $(CCPLR)/h/pmbitmap.h $(CCPLR)/h/pmdev.h \
	$(CCPLR)/h/pmerr.h $(CCPLR)/h/pmfont.h $(CCPLR)/h/pmgpi.h \
	$(CCPLR)/h/pmhelp.h $(CCPLR)/h/pmmle.h $(CCPLR)/h/pmord.h \
	$(CCPLR)/h/pmpic.h $(CCPLR)/h/pmshl.h $(CCPLR)/h/pmtypes.h \
	$(CCPLR)/h/pmwin.h $(CCPLR)/h/stddef.h $(CCPLR)/h/stdlib.h \
	$(CCPLR)/h/time.h $(COMMON)/H/access.h $(COMMON)/H/alert.h \
	$(COMMON)/H/alertmsg.h $(COMMON)/H/audit.h $(COMMON)/H/chardev.h \
	$(COMMON)/H/config.h $(COMMON)/H/errlog.h $(COMMON)/H/icanon.h \
	$(COMMON)/H/lan.h $(COMMON)/H/mailslot.h $(COMMON)/H/message.h \
	$(COMMON)/H/ncb.h $(COMMON)/H/net32def.h $(COMMON)/H/netbios.h \
	$(COMMON)/H/netcons.h $(COMMON)/H/neterr.h $(COMMON)/H/netstats.h \
	$(COMMON)/H/nmpipe.h $(COMMON)/H/profile.h $(COMMON)/H/remutil.h \
	$(COMMON)/H/server.h $(COMMON)/H/service.h $(COMMON)/H/shares.h \
	$(COMMON)/H/use.h $(COMMON)/H/wksta.h $(UI)/common/h/array.hxx \
	$(UI)/common/h/base.hxx $(UI)/common/h/blt.hxx \
	$(UI)/common/h/bltaccel.hxx $(UI)/common/h/bltapp.hxx \
	$(UI)/common/h/bltarrow.hxx $(UI)/common/h/bltatom.hxx \
	$(UI)/common/h/bltbitmp.hxx $(UI)/common/h/bltbutn.hxx \
	$(UI)/common/h/bltcc.hxx $(UI)/common/h/bltclwin.hxx \
	$(UI)/common/h/bltcolh.hxx $(UI)/common/h/bltcons.h \
	$(UI)/common/h/bltctlvl.hxx $(UI)/common/h/bltctrl.hxx \
	$(UI)/common/h/bltcurs.hxx $(UI)/common/h/bltdc.hxx \
	$(UI)/common/h/bltdisph.hxx $(UI)/common/h/bltdlg.hxx \
	$(UI)/common/h/bltedit.hxx $(UI)/common/h/bltevent.hxx \
	$(UI)/common/h/bltfont.hxx $(UI)/common/h/bltfunc.hxx \
	$(UI)/common/h/bltglob.hxx $(UI)/common/h/bltgroup.hxx \
	$(UI)/common/h/bltinit.hxx $(UI)/common/h/bltlb.hxx \
	$(UI)/common/h/bltlc.hxx $(UI)/common/h/bltmain.hxx \
	$(UI)/common/h/bltmisc.hxx $(UI)/common/h/bltmitem.hxx \
	$(UI)/common/h/bltmsgp.hxx $(UI)/common/h/bltpump.hxx \
	$(UI)/common/h/bltrc.h $(UI)/common/h/bltrect.hxx \
	$(UI)/common/h/bltsb.hxx $(UI)/common/h/bltsetbx.hxx \
	$(UI)/common/h/bltsi.hxx $(UI)/common/h/bltspobj.hxx \
	$(UI)/common/h/bltsslt.hxx $(UI)/common/h/bltssn.hxx \
	$(UI)/common/h/bltssnv.hxx $(UI)/common/h/bltsss.hxx \
	$(UI)/common/h/blttd.hxx $(UI)/common/h/blttm.hxx \
	$(UI)/common/h/bltwin.hxx $(UI)/common/h/ctime.hxx \
	$(UI)/common/h/dlist.hxx $(UI)/common/h/heap.hxx \
	$(UI)/common/h/intlprof.hxx $(UI)/common/h/lmui.hxx \
	$(UI)/common/h/lmuitype.h $(UI)/common/h/mnet32.h \
	$(UI)/common/h/mnettype.h $(UI)/common/h/slist.hxx \
	$(UI)/common/h/string.hxx $(UI)/common/h/strlst.hxx \
	$(UI)/common/h/uiassert.hxx $(UI)/common/h/uibuffer.hxx \
	$(UI)/common/h/uitrace.hxx $(UI)/common/hack/dos/dos.h \
	$(UI)/common/hack/dos/netlib.h $(UI)/common/hack/dos/pwin.h \
	$(UI)/common/hack/dos/pwin16.h $(UI)/common/hack/dos/pwintype.h \
	$(UI)/common/hack/dos/windows.h $(UI)/common/hack/os2def.h ./ta.h \
	./ta.hxx ./tester.hxx

./icon.obj ./icon.lst: ./icon.cxx $(CCPLR)/h/bse.h $(CCPLR)/h/bsedev.h \
	$(CCPLR)/h/bsedos.h $(CCPLR)/h/bseerr.h $(CCPLR)/h/bsesub.h \
	$(CCPLR)/h/os2.h $(CCPLR)/h/pm.h $(CCPLR)/h/pmavio.h \
	$(CCPLR)/h/pmbitmap.h $(CCPLR)/h/pmdev.h $(CCPLR)/h/pmerr.h \
	$(CCPLR)/h/pmfont.h $(CCPLR)/h/pmgpi.h $(CCPLR)/h/pmhelp.h \
	$(CCPLR)/h/pmmle.h $(CCPLR)/h/pmord.h $(CCPLR)/h/pmpic.h \
	$(CCPLR)/h/pmshl.h $(CCPLR)/h/pmtypes.h $(CCPLR)/h/pmwin.h \
	$(CCPLR)/h/stddef.h $(CCPLR)/h/stdlib.h $(CCPLR)/h/time.h \
	$(COMMON)/H/access.h $(COMMON)/H/alert.h $(COMMON)/H/alertmsg.h \
	$(COMMON)/H/audit.h $(COMMON)/H/chardev.h $(COMMON)/H/config.h \
	$(COMMON)/H/errlog.h $(COMMON)/H/icanon.h $(COMMON)/H/lan.h \
	$(COMMON)/H/mailslot.h $(COMMON)/H/message.h $(COMMON)/H/ncb.h \
	$(COMMON)/H/net32def.h $(COMMON)/H/netbios.h $(COMMON)/H/netcons.h \
	$(COMMON)/H/neterr.h $(COMMON)/H/netstats.h $(COMMON)/H/nmpipe.h \
	$(COMMON)/H/profile.h $(COMMON)/H/remutil.h $(COMMON)/H/server.h \
	$(COMMON)/H/service.h $(COMMON)/H/shares.h $(COMMON)/H/use.h \
	$(COMMON)/H/wksta.h $(UI)/common/h/array.hxx $(UI)/common/h/base.hxx \
	$(UI)/common/h/blt.hxx $(UI)/common/h/bltaccel.hxx \
	$(UI)/common/h/bltapp.hxx $(UI)/common/h/bltarrow.hxx \
	$(UI)/common/h/bltatom.hxx $(UI)/common/h/bltbitmp.hxx \
	$(UI)/common/h/bltbutn.hxx $(UI)/common/h/bltcc.hxx \
	$(UI)/common/h/bltclwin.hxx $(UI)/common/h/bltcolh.hxx \
	$(UI)/common/h/bltcons.h $(UI)/common/h/bltctlvl.hxx \
	$(UI)/common/h/bltctrl.hxx $(UI)/common/h/bltcurs.hxx \
	$(UI)/common/h/bltdc.hxx $(UI)/common/h/bltdisph.hxx \
	$(UI)/common/h/bltdlg.hxx $(UI)/common/h/bltedit.hxx \
	$(UI)/common/h/bltevent.hxx $(UI)/common/h/bltfont.hxx \
	$(UI)/common/h/bltfunc.hxx $(UI)/common/h/bltglob.hxx \
	$(UI)/common/h/bltgroup.hxx $(UI)/common/h/bltinit.hxx \
	$(UI)/common/h/bltlb.hxx $(UI)/common/h/bltlc.hxx \
	$(UI)/common/h/bltmain.hxx $(UI)/common/h/bltmisc.hxx \
	$(UI)/common/h/bltmitem.hxx $(UI)/common/h/bltmsgp.hxx \
	$(UI)/common/h/bltpump.hxx $(UI)/common/h/bltrc.h \
	$(UI)/common/h/bltrect.hxx $(UI)/common/h/bltsb.hxx \
	$(UI)/common/h/bltsetbx.hxx $(UI)/common/h/bltsi.hxx \
	$(UI)/common/h/bltspobj.hxx $(UI)/common/h/bltsslt.hxx \
	$(UI)/common/h/bltssn.hxx $(UI)/common/h/bltssnv.hxx \
	$(UI)/common/h/bltsss.hxx $(UI)/common/h/blttd.hxx \
	$(UI)/common/h/blttm.hxx $(UI)/common/h/bltwin.hxx \
	$(UI)/common/h/ctime.hxx $(UI)/common/h/dlist.hxx \
	$(UI)/common/h/heap.hxx $(UI)/common/h/intlprof.hxx \
	$(UI)/common/h/lmui.hxx $(UI)/common/h/lmuitype.h \
	$(UI)/common/h/mnet32.h $(UI)/common/h/mnettype.h \
	$(UI)/common/h/slist.hxx $(UI)/common/h/string.hxx \
	$(UI)/common/h/strlst.hxx $(UI)/common/h/uiassert.hxx \
	$(UI)/common/h/uibuffer.hxx $(UI)/common/h/uitrace.hxx \
	$(UI)/common/hack/dos/dos.h $(UI)/common/hack/dos/netlib.h \
	$(UI)/common/hack/dos/pwin.h $(UI)/common/hack/dos/pwin16.h \
	$(UI)/common/hack/dos/pwintype.h $(UI)/common/hack/dos/windows.h \
	$(UI)/common/hack/os2def.h ./ta.h ./ta.hxx ./tester.hxx

./password.obj ./password.lst: ./password.cxx $(CCPLR)/h/bse.h \
	$(CCPLR)/h/bsedev.h $(CCPLR)/h/bsedos.h $(CCPLR)/h/bseerr.h \
	$(CCPLR)/h/bsesub.h $(CCPLR)/h/os2.h $(CCPLR)/h/pm.h \
	$(CCPLR)/h/pmavio.h $(CCPLR)/h/pmbitmap.h $(CCPLR)/h/pmdev.h \
	$(CCPLR)/h/pmerr.h $(CCPLR)/h/pmfont.h $(CCPLR)/h/pmgpi.h \
	$(CCPLR)/h/pmhelp.h $(CCPLR)/h/pmmle.h $(CCPLR)/h/pmord.h \
	$(CCPLR)/h/pmpic.h $(CCPLR)/h/pmshl.h $(CCPLR)/h/pmtypes.h \
	$(CCPLR)/h/pmwin.h $(CCPLR)/h/stddef.h $(CCPLR)/h/stdlib.h \
	$(CCPLR)/h/time.h $(COMMON)/H/access.h $(COMMON)/H/alert.h \
	$(COMMON)/H/alertmsg.h $(COMMON)/H/audit.h $(COMMON)/H/chardev.h \
	$(COMMON)/H/config.h $(COMMON)/H/errlog.h $(COMMON)/H/icanon.h \
	$(COMMON)/H/lan.h $(COMMON)/H/mailslot.h $(COMMON)/H/message.h \
	$(COMMON)/H/ncb.h $(COMMON)/H/net32def.h $(COMMON)/H/netbios.h \
	$(COMMON)/H/netcons.h $(COMMON)/H/neterr.h $(COMMON)/H/netstats.h \
	$(COMMON)/H/nmpipe.h $(COMMON)/H/profile.h $(COMMON)/H/remutil.h \
	$(COMMON)/H/server.h $(COMMON)/H/service.h $(COMMON)/H/shares.h \
	$(COMMON)/H/use.h $(COMMON)/H/wksta.h $(UI)/common/h/array.hxx \
	$(UI)/common/h/base.hxx $(UI)/common/h/blt.hxx \
	$(UI)/common/h/bltaccel.hxx $(UI)/common/h/bltapp.hxx \
	$(UI)/common/h/bltarrow.hxx $(UI)/common/h/bltatom.hxx \
	$(UI)/common/h/bltbitmp.hxx $(UI)/common/h/bltbutn.hxx \
	$(UI)/common/h/bltcc.hxx $(UI)/common/h/bltclwin.hxx \
	$(UI)/common/h/bltcolh.hxx $(UI)/common/h/bltcons.h \
	$(UI)/common/h/bltctlvl.hxx $(UI)/common/h/bltctrl.hxx \
	$(UI)/common/h/bltcurs.hxx $(UI)/common/h/bltdc.hxx \
	$(UI)/common/h/bltdisph.hxx $(UI)/common/h/bltdlg.hxx \
	$(UI)/common/h/bltedit.hxx $(UI)/common/h/bltevent.hxx \
	$(UI)/common/h/bltfont.hxx $(UI)/common/h/bltfunc.hxx \
	$(UI)/common/h/bltglob.hxx $(UI)/common/h/bltgroup.hxx \
	$(UI)/common/h/bltinit.hxx $(UI)/common/h/bltlb.hxx \
	$(UI)/common/h/bltlc.hxx $(UI)/common/h/bltmain.hxx \
	$(UI)/common/h/bltmisc.hxx $(UI)/common/h/bltmitem.hxx \
	$(UI)/common/h/bltmsgp.hxx $(UI)/common/h/bltpump.hxx \
	$(UI)/common/h/bltrc.h $(UI)/common/h/bltrect.hxx \
	$(UI)/common/h/bltsb.hxx $(UI)/common/h/bltsetbx.hxx \
	$(UI)/common/h/bltsi.hxx $(UI)/common/h/bltspobj.hxx \
	$(UI)/common/h/bltsslt.hxx $(UI)/common/h/bltssn.hxx \
	$(UI)/common/h/bltssnv.hxx $(UI)/common/h/bltsss.hxx \
	$(UI)/common/h/blttd.hxx $(UI)/common/h/blttm.hxx \
	$(UI)/common/h/bltwin.hxx $(UI)/common/h/ctime.hxx \
	$(UI)/common/h/dlist.hxx $(UI)/common/h/heap.hxx \
	$(UI)/common/h/intlprof.hxx $(UI)/common/h/lmui.hxx \
	$(UI)/common/h/lmuitype.h $(UI)/common/h/mnet32.h \
	$(UI)/common/h/mnettype.h $(UI)/common/h/slist.hxx \
	$(UI)/common/h/string.hxx $(UI)/common/h/strlst.hxx \
	$(UI)/common/h/uiassert.hxx $(UI)/common/h/uibuffer.hxx \
	$(UI)/common/h/uitrace.hxx $(UI)/common/hack/dos/dos.h \
	$(UI)/common/hack/dos/netlib.h $(UI)/common/hack/dos/pwin.h \
	$(UI)/common/hack/dos/pwin16.h $(UI)/common/hack/dos/pwintype.h \
	$(UI)/common/hack/dos/windows.h $(UI)/common/hack/os2def.h ./ta.h \
	./ta.hxx ./tester.hxx

./mle.obj ./mle.lst: ./mle.cxx $(CCPLR)/h/bse.h $(CCPLR)/h/bsedev.h \
	$(CCPLR)/h/bsedos.h $(CCPLR)/h/bseerr.h $(CCPLR)/h/bsesub.h \
	$(CCPLR)/h/os2.h $(CCPLR)/h/pm.h $(CCPLR)/h/pmavio.h \
	$(CCPLR)/h/pmbitmap.h $(CCPLR)/h/pmdev.h $(CCPLR)/h/pmerr.h \
	$(CCPLR)/h/pmfont.h $(CCPLR)/h/pmgpi.h $(CCPLR)/h/pmhelp.h \
	$(CCPLR)/h/pmmle.h $(CCPLR)/h/pmord.h $(CCPLR)/h/pmpic.h \
	$(CCPLR)/h/pmshl.h $(CCPLR)/h/pmtypes.h $(CCPLR)/h/pmwin.h \
	$(CCPLR)/h/stddef.h $(CCPLR)/h/stdlib.h $(CCPLR)/h/time.h \
	$(COMMON)/H/access.h $(COMMON)/H/alert.h $(COMMON)/H/alertmsg.h \
	$(COMMON)/H/audit.h $(COMMON)/H/chardev.h $(COMMON)/H/config.h \
	$(COMMON)/H/errlog.h $(COMMON)/H/icanon.h $(COMMON)/H/lan.h \
	$(COMMON)/H/mailslot.h $(COMMON)/H/message.h $(COMMON)/H/ncb.h \
	$(COMMON)/H/net32def.h $(COMMON)/H/netbios.h $(COMMON)/H/netcons.h \
	$(COMMON)/H/neterr.h $(COMMON)/H/netstats.h $(COMMON)/H/nmpipe.h \
	$(COMMON)/H/profile.h $(COMMON)/H/remutil.h $(COMMON)/H/server.h \
	$(COMMON)/H/service.h $(COMMON)/H/shares.h $(COMMON)/H/use.h \
	$(COMMON)/H/wksta.h $(UI)/common/h/array.hxx $(UI)/common/h/base.hxx \
	$(UI)/common/h/blt.hxx $(UI)/common/h/bltaccel.hxx \
	$(UI)/common/h/bltapp.hxx $(UI)/common/h/bltarrow.hxx \
	$(UI)/common/h/bltatom.hxx $(UI)/common/h/bltbitmp.hxx \
	$(UI)/common/h/bltbutn.hxx $(UI)/common/h/bltcc.hxx \
	$(UI)/common/h/bltclwin.hxx $(UI)/common/h/bltcolh.hxx \
	$(UI)/common/h/bltcons.h $(UI)/common/h/bltctlvl.hxx \
	$(UI)/common/h/bltctrl.hxx $(UI)/common/h/bltcurs.hxx \
	$(UI)/common/h/bltdc.hxx $(UI)/common/h/bltdisph.hxx \
	$(UI)/common/h/bltdlg.hxx $(UI)/common/h/bltedit.hxx \
	$(UI)/common/h/bltevent.hxx $(UI)/common/h/bltfont.hxx \
	$(UI)/common/h/bltfunc.hxx $(UI)/common/h/bltglob.hxx \
	$(UI)/common/h/bltgroup.hxx $(UI)/common/h/bltinit.hxx \
	$(UI)/common/h/bltlb.hxx $(UI)/common/h/bltlc.hxx \
	$(UI)/common/h/bltmain.hxx $(UI)/common/h/bltmisc.hxx \
	$(UI)/common/h/bltmitem.hxx $(UI)/common/h/bltmsgp.hxx \
	$(UI)/common/h/bltpump.hxx $(UI)/common/h/bltrc.h \
	$(UI)/common/h/bltrect.hxx $(UI)/common/h/bltsb.hxx \
	$(UI)/common/h/bltsetbx.hxx $(UI)/common/h/bltsi.hxx \
	$(UI)/common/h/bltspobj.hxx $(UI)/common/h/bltsslt.hxx \
	$(UI)/common/h/bltssn.hxx $(UI)/common/h/bltssnv.hxx \
	$(UI)/common/h/bltsss.hxx $(UI)/common/h/blttd.hxx \
	$(UI)/common/h/blttm.hxx $(UI)/common/h/bltwin.hxx \
	$(UI)/common/h/ctime.hxx $(UI)/common/h/dlist.hxx \
	$(UI)/common/h/heap.hxx $(UI)/common/h/intlprof.hxx \
	$(UI)/common/h/lmui.hxx $(UI)/common/h/lmuitype.h \
	$(UI)/common/h/mnet32.h $(UI)/common/h/mnettype.h \
	$(UI)/common/h/slist.hxx $(UI)/common/h/string.hxx \
	$(UI)/common/h/strlst.hxx $(UI)/common/h/uiassert.hxx \
	$(UI)/common/h/uibuffer.hxx $(UI)/common/h/uitrace.hxx \
	$(UI)/common/hack/dos/dos.h $(UI)/common/hack/dos/netlib.h \
	$(UI)/common/hack/dos/pwin.h $(UI)/common/hack/dos/pwin16.h \
	$(UI)/common/hack/dos/pwintype.h $(UI)/common/hack/dos/windows.h \
	$(UI)/common/hack/os2def.h ./ta.h ./ta.hxx ./tester.hxx

./radiobut.obj ./radiobut.lst: ./radiobut.cxx $(CCPLR)/h/bse.h \
	$(CCPLR)/h/bsedev.h $(CCPLR)/h/bsedos.h $(CCPLR)/h/bseerr.h \
	$(CCPLR)/h/bsesub.h $(CCPLR)/h/os2.h $(CCPLR)/h/pm.h \
	$(CCPLR)/h/pmavio.h $(CCPLR)/h/pmbitmap.h $(CCPLR)/h/pmdev.h \
	$(CCPLR)/h/pmerr.h $(CCPLR)/h/pmfont.h $(CCPLR)/h/pmgpi.h \
	$(CCPLR)/h/pmhelp.h $(CCPLR)/h/pmmle.h $(CCPLR)/h/pmord.h \
	$(CCPLR)/h/pmpic.h $(CCPLR)/h/pmshl.h $(CCPLR)/h/pmtypes.h \
	$(CCPLR)/h/pmwin.h $(CCPLR)/h/stddef.h $(CCPLR)/h/stdlib.h \
	$(CCPLR)/h/time.h $(COMMON)/H/access.h $(COMMON)/H/alert.h \
	$(COMMON)/H/alertmsg.h $(COMMON)/H/audit.h $(COMMON)/H/chardev.h \
	$(COMMON)/H/config.h $(COMMON)/H/errlog.h $(COMMON)/H/icanon.h \
	$(COMMON)/H/lan.h $(COMMON)/H/mailslot.h $(COMMON)/H/message.h \
	$(COMMON)/H/ncb.h $(COMMON)/H/net32def.h $(COMMON)/H/netbios.h \
	$(COMMON)/H/netcons.h $(COMMON)/H/neterr.h $(COMMON)/H/netstats.h \
	$(COMMON)/H/nmpipe.h $(COMMON)/H/profile.h $(COMMON)/H/remutil.h \
	$(COMMON)/H/server.h $(COMMON)/H/service.h $(COMMON)/H/shares.h \
	$(COMMON)/H/use.h $(COMMON)/H/wksta.h $(UI)/common/h/array.hxx \
	$(UI)/common/h/base.hxx $(UI)/common/h/blt.hxx \
	$(UI)/common/h/bltaccel.hxx $(UI)/common/h/bltapp.hxx \
	$(UI)/common/h/bltarrow.hxx $(UI)/common/h/bltatom.hxx \
	$(UI)/common/h/bltbitmp.hxx $(UI)/common/h/bltbutn.hxx \
	$(UI)/common/h/bltcc.hxx $(UI)/common/h/bltclwin.hxx \
	$(UI)/common/h/bltcolh.hxx $(UI)/common/h/bltcons.h \
	$(UI)/common/h/bltctlvl.hxx $(UI)/common/h/bltctrl.hxx \
	$(UI)/common/h/bltcurs.hxx $(UI)/common/h/bltdc.hxx \
	$(UI)/common/h/bltdisph.hxx $(UI)/common/h/bltdlg.hxx \
	$(UI)/common/h/bltedit.hxx $(UI)/common/h/bltevent.hxx \
	$(UI)/common/h/bltfont.hxx $(UI)/common/h/bltfunc.hxx \
	$(UI)/common/h/bltglob.hxx $(UI)/common/h/bltgroup.hxx \
	$(UI)/common/h/bltinit.hxx $(UI)/common/h/bltlb.hxx \
	$(UI)/common/h/bltlc.hxx $(UI)/common/h/bltmain.hxx \
	$(UI)/common/h/bltmisc.hxx $(UI)/common/h/bltmitem.hxx \
	$(UI)/common/h/bltmsgp.hxx $(UI)/common/h/bltpump.hxx \
	$(UI)/common/h/bltrc.h $(UI)/common/h/bltrect.hxx \
	$(UI)/common/h/bltsb.hxx $(UI)/common/h/bltsetbx.hxx \
	$(UI)/common/h/bltsi.hxx $(UI)/common/h/bltspobj.hxx \
	$(UI)/common/h/bltsslt.hxx $(UI)/common/h/bltssn.hxx \
	$(UI)/common/h/bltssnv.hxx $(UI)/common/h/bltsss.hxx \
	$(UI)/common/h/blttd.hxx $(UI)/common/h/blttm.hxx \
	$(UI)/common/h/bltwin.hxx $(UI)/common/h/ctime.hxx \
	$(UI)/common/h/dlist.hxx $(UI)/common/h/heap.hxx \
	$(UI)/common/h/intlprof.hxx $(UI)/common/h/lmui.hxx \
	$(UI)/common/h/lmuitype.h $(UI)/common/h/mnet32.h \
	$(UI)/common/h/mnettype.h $(UI)/common/h/slist.hxx \
	$(UI)/common/h/string.hxx $(UI)/common/h/strlst.hxx \
	$(UI)/common/h/uiassert.hxx $(UI)/common/h/uibuffer.hxx \
	$(UI)/common/h/uitrace.hxx $(UI)/common/hack/dos/dos.h \
	$(UI)/common/hack/dos/netlib.h $(UI)/common/hack/dos/pwin.h \
	$(UI)/common/hack/dos/pwin16.h $(UI)/common/hack/dos/pwintype.h \
	$(UI)/common/hack/dos/windows.h $(UI)/common/hack/os2def.h ./ta.h \
	./ta.hxx ./tester.hxx

./pushbut.obj ./pushbut.lst: ./pushbut.cxx $(CCPLR)/h/bse.h \
	$(CCPLR)/h/bsedev.h $(CCPLR)/h/bsedos.h $(CCPLR)/h/bseerr.h \
	$(CCPLR)/h/bsesub.h $(CCPLR)/h/os2.h $(CCPLR)/h/pm.h \
	$(CCPLR)/h/pmavio.h $(CCPLR)/h/pmbitmap.h $(CCPLR)/h/pmdev.h \
	$(CCPLR)/h/pmerr.h $(CCPLR)/h/pmfont.h $(CCPLR)/h/pmgpi.h \
	$(CCPLR)/h/pmhelp.h $(CCPLR)/h/pmmle.h $(CCPLR)/h/pmord.h \
	$(CCPLR)/h/pmpic.h $(CCPLR)/h/pmshl.h $(CCPLR)/h/pmtypes.h \
	$(CCPLR)/h/pmwin.h $(CCPLR)/h/stddef.h $(CCPLR)/h/stdlib.h \
	$(CCPLR)/h/time.h $(COMMON)/H/access.h $(COMMON)/H/alert.h \
	$(COMMON)/H/alertmsg.h $(COMMON)/H/audit.h $(COMMON)/H/chardev.h \
	$(COMMON)/H/config.h $(COMMON)/H/errlog.h $(COMMON)/H/icanon.h \
	$(COMMON)/H/lan.h $(COMMON)/H/mailslot.h $(COMMON)/H/message.h \
	$(COMMON)/H/ncb.h $(COMMON)/H/net32def.h $(COMMON)/H/netbios.h \
	$(COMMON)/H/netcons.h $(COMMON)/H/neterr.h $(COMMON)/H/netstats.h \
	$(COMMON)/H/nmpipe.h $(COMMON)/H/profile.h $(COMMON)/H/remutil.h \
	$(COMMON)/H/server.h $(COMMON)/H/service.h $(COMMON)/H/shares.h \
	$(COMMON)/H/use.h $(COMMON)/H/wksta.h $(UI)/common/h/array.hxx \
	$(UI)/common/h/base.hxx $(UI)/common/h/blt.hxx \
	$(UI)/common/h/bltaccel.hxx $(UI)/common/h/bltapp.hxx \
	$(UI)/common/h/bltarrow.hxx $(UI)/common/h/bltatom.hxx \
	$(UI)/common/h/bltbitmp.hxx $(UI)/common/h/bltbutn.hxx \
	$(UI)/common/h/bltcc.hxx $(UI)/common/h/bltclwin.hxx \
	$(UI)/common/h/bltcolh.hxx $(UI)/common/h/bltcons.h \
	$(UI)/common/h/bltctlvl.hxx $(UI)/common/h/bltctrl.hxx \
	$(UI)/common/h/bltcurs.hxx $(UI)/common/h/bltdc.hxx \
	$(UI)/common/h/bltdisph.hxx $(UI)/common/h/bltdlg.hxx \
	$(UI)/common/h/bltedit.hxx $(UI)/common/h/bltevent.hxx \
	$(UI)/common/h/bltfont.hxx $(UI)/common/h/bltfunc.hxx \
	$(UI)/common/h/bltglob.hxx $(UI)/common/h/bltgroup.hxx \
	$(UI)/common/h/bltinit.hxx $(UI)/common/h/bltlb.hxx \
	$(UI)/common/h/bltlc.hxx $(UI)/common/h/bltmain.hxx \
	$(UI)/common/h/bltmisc.hxx $(UI)/common/h/bltmitem.hxx \
	$(UI)/common/h/bltmsgp.hxx $(UI)/common/h/bltpump.hxx \
	$(UI)/common/h/bltrc.h $(UI)/common/h/bltrect.hxx \
	$(UI)/common/h/bltsb.hxx $(UI)/common/h/bltsetbx.hxx \
	$(UI)/common/h/bltsi.hxx $(UI)/common/h/bltspobj.hxx \
	$(UI)/common/h/bltsslt.hxx $(UI)/common/h/bltssn.hxx \
	$(UI)/common/h/bltssnv.hxx $(UI)/common/h/bltsss.hxx \
	$(UI)/common/h/blttd.hxx $(UI)/common/h/blttm.hxx \
	$(UI)/common/h/bltwin.hxx $(UI)/common/h/ctime.hxx \
	$(UI)/common/h/dlist.hxx $(UI)/common/h/heap.hxx \
	$(UI)/common/h/intlprof.hxx $(UI)/common/h/lmui.hxx \
	$(UI)/common/h/lmuitype.h $(UI)/common/h/mnet32.h \
	$(UI)/common/h/mnettype.h $(UI)/common/h/slist.hxx \
	$(UI)/common/h/string.hxx $(UI)/common/h/strlst.hxx \
	$(UI)/common/h/uiassert.hxx $(UI)/common/h/uibuffer.hxx \
	$(UI)/common/h/uitrace.hxx $(UI)/common/hack/dos/dos.h \
	$(UI)/common/hack/dos/netlib.h $(UI)/common/hack/dos/pwin.h \
	$(UI)/common/hack/dos/pwin16.h $(UI)/common/hack/dos/pwintype.h \
	$(UI)/common/hack/dos/windows.h $(UI)/common/hack/os2def.h ./ta.h \
	./ta.hxx ./tester.hxx

./slt.obj ./slt.lst: ./slt.cxx $(CCPLR)/h/bse.h $(CCPLR)/h/bsedev.h \
	$(CCPLR)/h/bsedos.h $(CCPLR)/h/bseerr.h $(CCPLR)/h/bsesub.h \
	$(CCPLR)/h/os2.h $(CCPLR)/h/pm.h $(CCPLR)/h/pmavio.h \
	$(CCPLR)/h/pmbitmap.h $(CCPLR)/h/pmdev.h $(CCPLR)/h/pmerr.h \
	$(CCPLR)/h/pmfont.h $(CCPLR)/h/pmgpi.h $(CCPLR)/h/pmhelp.h \
	$(CCPLR)/h/pmmle.h $(CCPLR)/h/pmord.h $(CCPLR)/h/pmpic.h \
	$(CCPLR)/h/pmshl.h $(CCPLR)/h/pmtypes.h $(CCPLR)/h/pmwin.h \
	$(CCPLR)/h/stddef.h $(CCPLR)/h/stdlib.h $(CCPLR)/h/time.h \
	$(COMMON)/H/access.h $(COMMON)/H/alert.h $(COMMON)/H/alertmsg.h \
	$(COMMON)/H/audit.h $(COMMON)/H/chardev.h $(COMMON)/H/config.h \
	$(COMMON)/H/errlog.h $(COMMON)/H/icanon.h $(COMMON)/H/lan.h \
	$(COMMON)/H/mailslot.h $(COMMON)/H/message.h $(COMMON)/H/ncb.h \
	$(COMMON)/H/net32def.h $(COMMON)/H/netbios.h $(COMMON)/H/netcons.h \
	$(COMMON)/H/neterr.h $(COMMON)/H/netstats.h $(COMMON)/H/nmpipe.h \
	$(COMMON)/H/profile.h $(COMMON)/H/remutil.h $(COMMON)/H/server.h \
	$(COMMON)/H/service.h $(COMMON)/H/shares.h $(COMMON)/H/use.h \
	$(COMMON)/H/wksta.h $(UI)/common/h/array.hxx $(UI)/common/h/base.hxx \
	$(UI)/common/h/blt.hxx $(UI)/common/h/bltaccel.hxx \
	$(UI)/common/h/bltapp.hxx $(UI)/common/h/bltarrow.hxx \
	$(UI)/common/h/bltatom.hxx $(UI)/common/h/bltbitmp.hxx \
	$(UI)/common/h/bltbutn.hxx $(UI)/common/h/bltcc.hxx \
	$(UI)/common/h/bltclwin.hxx $(UI)/common/h/bltcolh.hxx \
	$(UI)/common/h/bltcons.h $(UI)/common/h/bltctlvl.hxx \
	$(UI)/common/h/bltctrl.hxx $(UI)/common/h/bltcurs.hxx \
	$(UI)/common/h/bltdc.hxx $(UI)/common/h/bltdisph.hxx \
	$(UI)/common/h/bltdlg.hxx $(UI)/common/h/bltedit.hxx \
	$(UI)/common/h/bltevent.hxx $(UI)/common/h/bltfont.hxx \
	$(UI)/common/h/bltfunc.hxx $(UI)/common/h/bltglob.hxx \
	$(UI)/common/h/bltgroup.hxx $(UI)/common/h/bltinit.hxx \
	$(UI)/common/h/bltlb.hxx $(UI)/common/h/bltlc.hxx \
	$(UI)/common/h/bltmain.hxx $(UI)/common/h/bltmisc.hxx \
	$(UI)/common/h/bltmitem.hxx $(UI)/common/h/bltmsgp.hxx \
	$(UI)/common/h/bltpump.hxx $(UI)/common/h/bltrc.h \
	$(UI)/common/h/bltrect.hxx $(UI)/common/h/bltsb.hxx \
	$(UI)/common/h/bltsetbx.hxx $(UI)/common/h/bltsi.hxx \
	$(UI)/common/h/bltspobj.hxx $(UI)/common/h/bltsslt.hxx \
	$(UI)/common/h/bltssn.hxx $(UI)/common/h/bltssnv.hxx \
	$(UI)/common/h/bltsss.hxx $(UI)/common/h/blttd.hxx \
	$(UI)/common/h/blttm.hxx $(UI)/common/h/bltwin.hxx \
	$(UI)/common/h/ctime.hxx $(UI)/common/h/dlist.hxx \
	$(UI)/common/h/heap.hxx $(UI)/common/h/intlprof.hxx \
	$(UI)/common/h/lmui.hxx $(UI)/common/h/lmuitype.h \
	$(UI)/common/h/mnet32.h $(UI)/common/h/mnettype.h \
	$(UI)/common/h/slist.hxx $(UI)/common/h/string.hxx \
	$(UI)/common/h/strlst.hxx $(UI)/common/h/uiassert.hxx \
	$(UI)/common/h/uibuffer.hxx $(UI)/common/h/uitrace.hxx \
	$(UI)/common/hack/dos/dos.h $(UI)/common/hack/dos/netlib.h \
	$(UI)/common/hack/dos/pwin.h $(UI)/common/hack/dos/pwin16.h \
	$(UI)/common/hack/dos/pwintype.h $(UI)/common/hack/dos/windows.h \
	$(UI)/common/hack/os2def.h ./ta.h ./ta.hxx ./tester.hxx

./sle.obj ./sle.lst: ./sle.cxx $(CCPLR)/h/bse.h $(CCPLR)/h/bsedev.h \
	$(CCPLR)/h/bsedos.h $(CCPLR)/h/bseerr.h $(CCPLR)/h/bsesub.h \
	$(CCPLR)/h/os2.h $(CCPLR)/h/pm.h $(CCPLR)/h/pmavio.h \
	$(CCPLR)/h/pmbitmap.h $(CCPLR)/h/pmdev.h $(CCPLR)/h/pmerr.h \
	$(CCPLR)/h/pmfont.h $(CCPLR)/h/pmgpi.h $(CCPLR)/h/pmhelp.h \
	$(CCPLR)/h/pmmle.h $(CCPLR)/h/pmord.h $(CCPLR)/h/pmpic.h \
	$(CCPLR)/h/pmshl.h $(CCPLR)/h/pmtypes.h $(CCPLR)/h/pmwin.h \
	$(CCPLR)/h/stddef.h $(CCPLR)/h/stdlib.h $(CCPLR)/h/time.h \
	$(COMMON)/H/access.h $(COMMON)/H/alert.h $(COMMON)/H/alertmsg.h \
	$(COMMON)/H/audit.h $(COMMON)/H/chardev.h $(COMMON)/H/config.h \
	$(COMMON)/H/errlog.h $(COMMON)/H/icanon.h $(COMMON)/H/lan.h \
	$(COMMON)/H/mailslot.h $(COMMON)/H/message.h $(COMMON)/H/ncb.h \
	$(COMMON)/H/net32def.h $(COMMON)/H/netbios.h $(COMMON)/H/netcons.h \
	$(COMMON)/H/neterr.h $(COMMON)/H/netstats.h $(COMMON)/H/nmpipe.h \
	$(COMMON)/H/profile.h $(COMMON)/H/remutil.h $(COMMON)/H/server.h \
	$(COMMON)/H/service.h $(COMMON)/H/shares.h $(COMMON)/H/use.h \
	$(COMMON)/H/wksta.h $(UI)/common/h/array.hxx $(UI)/common/h/base.hxx \
	$(UI)/common/h/blt.hxx $(UI)/common/h/bltaccel.hxx \
	$(UI)/common/h/bltapp.hxx $(UI)/common/h/bltarrow.hxx \
	$(UI)/common/h/bltatom.hxx $(UI)/common/h/bltbitmp.hxx \
	$(UI)/common/h/bltbutn.hxx $(UI)/common/h/bltcc.hxx \
	$(UI)/common/h/bltclwin.hxx $(UI)/common/h/bltcolh.hxx \
	$(UI)/common/h/bltcons.h $(UI)/common/h/bltctlvl.hxx \
	$(UI)/common/h/bltctrl.hxx $(UI)/common/h/bltcurs.hxx \
	$(UI)/common/h/bltdc.hxx $(UI)/common/h/bltdisph.hxx \
	$(UI)/common/h/bltdlg.hxx $(UI)/common/h/bltedit.hxx \
	$(UI)/common/h/bltevent.hxx $(UI)/common/h/bltfont.hxx \
	$(UI)/common/h/bltfunc.hxx $(UI)/common/h/bltglob.hxx \
	$(UI)/common/h/bltgroup.hxx $(UI)/common/h/bltinit.hxx \
	$(UI)/common/h/bltlb.hxx $(UI)/common/h/bltlc.hxx \
	$(UI)/common/h/bltmain.hxx $(UI)/common/h/bltmisc.hxx \
	$(UI)/common/h/bltmitem.hxx $(UI)/common/h/bltmsgp.hxx \
	$(UI)/common/h/bltpump.hxx $(UI)/common/h/bltrc.h \
	$(UI)/common/h/bltrect.hxx $(UI)/common/h/bltsb.hxx \
	$(UI)/common/h/bltsetbx.hxx $(UI)/common/h/bltsi.hxx \
	$(UI)/common/h/bltspobj.hxx $(UI)/common/h/bltsslt.hxx \
	$(UI)/common/h/bltssn.hxx $(UI)/common/h/bltssnv.hxx \
	$(UI)/common/h/bltsss.hxx $(UI)/common/h/blttd.hxx \
	$(UI)/common/h/blttm.hxx $(UI)/common/h/bltwin.hxx \
	$(UI)/common/h/ctime.hxx $(UI)/common/h/dlist.hxx \
	$(UI)/common/h/heap.hxx $(UI)/common/h/intlprof.hxx \
	$(UI)/common/h/lmui.hxx $(UI)/common/h/lmuitype.h \
	$(UI)/common/h/mnet32.h $(UI)/common/h/mnettype.h \
	$(UI)/common/h/slist.hxx $(UI)/common/h/string.hxx \
	$(UI)/common/h/strlst.hxx $(UI)/common/h/uiassert.hxx \
	$(UI)/common/h/uibuffer.hxx $(UI)/common/h/uitrace.hxx \
	$(UI)/common/hack/dos/dos.h $(UI)/common/hack/dos/netlib.h \
	$(UI)/common/hack/dos/pwin.h $(UI)/common/hack/dos/pwin16.h \
	$(UI)/common/hack/dos/pwintype.h $(UI)/common/hack/dos/windows.h \
	$(UI)/common/hack/os2def.h ./ta.h ./ta.hxx ./tester.hxx

./tester.obj ./tester.lst: ./tester.cxx $(CCPLR)/h/bse.h \
	$(CCPLR)/h/bsedev.h $(CCPLR)/h/bsedos.h $(CCPLR)/h/bseerr.h \
	$(CCPLR)/h/bsesub.h $(CCPLR)/h/os2.h $(CCPLR)/h/pm.h \
	$(CCPLR)/h/pmavio.h $(CCPLR)/h/pmbitmap.h $(CCPLR)/h/pmdev.h \
	$(CCPLR)/h/pmerr.h $(CCPLR)/h/pmfont.h $(CCPLR)/h/pmgpi.h \
	$(CCPLR)/h/pmhelp.h $(CCPLR)/h/pmmle.h $(CCPLR)/h/pmord.h \
	$(CCPLR)/h/pmpic.h $(CCPLR)/h/pmshl.h $(CCPLR)/h/pmtypes.h \
	$(CCPLR)/h/pmwin.h $(CCPLR)/h/stddef.h $(CCPLR)/h/stdlib.h \
	$(CCPLR)/h/time.h $(COMMON)/H/access.h $(COMMON)/H/alert.h \
	$(COMMON)/H/alertmsg.h $(COMMON)/H/audit.h $(COMMON)/H/chardev.h \
	$(COMMON)/H/config.h $(COMMON)/H/errlog.h $(COMMON)/H/icanon.h \
	$(COMMON)/H/lan.h $(COMMON)/H/mailslot.h $(COMMON)/H/message.h \
	$(COMMON)/H/ncb.h $(COMMON)/H/net32def.h $(COMMON)/H/netbios.h \
	$(COMMON)/H/netcons.h $(COMMON)/H/neterr.h $(COMMON)/H/netstats.h \
	$(COMMON)/H/nmpipe.h $(COMMON)/H/profile.h $(COMMON)/H/remutil.h \
	$(COMMON)/H/server.h $(COMMON)/H/service.h $(COMMON)/H/shares.h \
	$(COMMON)/H/use.h $(COMMON)/H/wksta.h $(UI)/common/h/array.hxx \
	$(UI)/common/h/base.hxx $(UI)/common/h/blt.hxx \
	$(UI)/common/h/bltaccel.hxx $(UI)/common/h/bltapp.hxx \
	$(UI)/common/h/bltarrow.hxx $(UI)/common/h/bltatom.hxx \
	$(UI)/common/h/bltbitmp.hxx $(UI)/common/h/bltbutn.hxx \
	$(UI)/common/h/bltcc.hxx $(UI)/common/h/bltclwin.hxx \
	$(UI)/common/h/bltcolh.hxx $(UI)/common/h/bltcons.h \
	$(UI)/common/h/bltctlvl.hxx $(UI)/common/h/bltctrl.hxx \
	$(UI)/common/h/bltcurs.hxx $(UI)/common/h/bltdc.hxx \
	$(UI)/common/h/bltdisph.hxx $(UI)/common/h/bltdlg.hxx \
	$(UI)/common/h/bltedit.hxx $(UI)/common/h/bltevent.hxx \
	$(UI)/common/h/bltfont.hxx $(UI)/common/h/bltfunc.hxx \
	$(UI)/common/h/bltglob.hxx $(UI)/common/h/bltgroup.hxx \
	$(UI)/common/h/bltinit.hxx $(UI)/common/h/bltlb.hxx \
	$(UI)/common/h/bltlc.hxx $(UI)/common/h/bltmain.hxx \
	$(UI)/common/h/bltmisc.hxx $(UI)/common/h/bltmitem.hxx \
	$(UI)/common/h/bltmsgp.hxx $(UI)/common/h/bltpump.hxx \
	$(UI)/common/h/bltrc.h $(UI)/common/h/bltrect.hxx \
	$(UI)/common/h/bltsb.hxx $(UI)/common/h/bltsetbx.hxx \
	$(UI)/common/h/bltsi.hxx $(UI)/common/h/bltspobj.hxx \
	$(UI)/common/h/bltsslt.hxx $(UI)/common/h/bltssn.hxx \
	$(UI)/common/h/bltssnv.hxx $(UI)/common/h/bltsss.hxx \
	$(UI)/common/h/blttd.hxx $(UI)/common/h/blttm.hxx \
	$(UI)/common/h/bltwin.hxx $(UI)/common/h/ctime.hxx \
	$(UI)/common/h/dlist.hxx $(UI)/common/h/heap.hxx \
	$(UI)/common/h/intlprof.hxx $(UI)/common/h/lmui.hxx \
	$(UI)/common/h/lmuitype.h $(UI)/common/h/mnet32.h \
	$(UI)/common/h/mnettype.h $(UI)/common/h/slist.hxx \
	$(UI)/common/h/string.hxx $(UI)/common/h/strlst.hxx \
	$(UI)/common/h/uiassert.hxx $(UI)/common/h/uibuffer.hxx \
	$(UI)/common/h/uitrace.hxx $(UI)/common/hack/dos/dos.h \
	$(UI)/common/hack/dos/netlib.h $(UI)/common/hack/dos/pwin.h \
	$(UI)/common/hack/dos/pwin16.h $(UI)/common/hack/dos/pwintype.h \
	$(UI)/common/hack/dos/windows.h $(UI)/common/hack/os2def.h ./ta.h \
	./ta.hxx ./tester.hxx

# IF YOU PUT STUFF HERE IT WILL GET BLASTED 
# see depend in makefile 
