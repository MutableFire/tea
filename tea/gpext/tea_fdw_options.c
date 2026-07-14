#include "tea/gpext/tea_fdw_options.h"

#include "commands/defrem.h"
#include "foreign/foreign.h"
#include "utils/elog.h"
#include "utils/errcodes.h"

char* TeaGetLocation(Oid foreigntableid) {
  ForeignTable* table;
  ListCell* lc;

  table = GetForeignTable(foreigntableid);

  foreach (lc, table->options) {
    DefElem* def = (DefElem*)lfirst(lc);

    if (strcmp(def->defname, "location") == 0) {
      return defGetString(def);
    }
  }

  ereport(ERROR, (errcode(ERRCODE_INVALID_PARAMETER_VALUE),
                  errmsg("missing required option \"location\" for foreign table %u", foreigntableid),
                  errdetail("The TEA foreign data wrapper requires the \"location\" option to be specified."),
                  errhint("Recreate the foreign table with OPTIONS (location '...').")));
}
