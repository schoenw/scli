#ifndef __G_SNMP_TABLE_H__
#define __G_SNMP_TABLE_H__

typedef struct _Gsnmp_table   Gsnmp_table;

struct _Gsnmp_table
{
  host_snmp  * host;
  GSList     * objs;
  gpointer     data;

  gpointer     request;

  void      (* cb_error)();
  void      (* cb_row)();
  void      (* cb_finish)();
};


Gsnmp_table * g_snmp_table_new (host_snmp *host, GSList *objs,
                  void (* cb_error)(), void (* cb_row)(), void (* cb_finish)(),
                  gpointer data);
void g_snmp_table_get(Gsnmp_table *table);
void g_snmp_table_destroy(Gsnmp_table *table);

#endif /* __G_SNMP_TABLE_H__ */
