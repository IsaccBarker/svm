#include <svm_class.h>

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void svm_print_class_overview(svm_class_representation* r) {
    printf(
            "Magic                 : %s\n"
            "Minor Version         : %d\n"
            "Major Version         : %d\n"
            "Constant Pool Count   : %d\n"
            "Access Flags          : %d\n"
            "This Class            : %d\n"
            "Super Class           : %d\n"
            "Interface Count       : %d\n"
            "Fields Count          : %d\n"
            "Methods Count         : %d\n"
            "Attribute Count       : %d\n",
            r->magic, r->minor_ver, r->major_ver, r->constant_pool_count,
            r->access_flags, r->this_class, r->super_class, r->interfaces_count,
            r->fields_count, r->methods_count, r-> attribute_count
            );
}

