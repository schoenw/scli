info_TEXINFOS = scli.texinfo
scli_TEXINFOS = gpl.texinfo

modes.texinfo: $(top_builddir)/scli/scli
	$(top_builddir)/scli/scli -n -c "show scli modes" | \
	awk '/^$$/		{ if (example) { \
				    printf("@end example\n"); \
				    example = 0; \
				  } \
				  if (verbatim) { \
				    printf("@end verbatim\n"); \
				    verbatim = 0; \
				  } \
				  printf("\n"); next } \
	     /^[A-Z][A-Z  ]*$$/	{ printf("@section %s\n", $$0); next } \
	     /^    /		{ if (! example) { \
				    printf("\n@example\n"); \
				    example = 1; \
				  } \
				  while (sub(/^ /, "")) ; \
				  while (sub(/ $$/, "")) ; \
				  printf("@command{%s}\n", $$0); \
				  next } \
	     /^  /		{ if (! verbatim) { \
				    printf("@verbatim\n"); \
				    verbatim = 1; \
				  } \
				  printf("%s\n", $$0); \
				  next } \
	     /^ $$/		{ next } \
	     //			{ printf("%s\n", $$0) }' > modes.texinfo

