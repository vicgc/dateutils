# Help the Developers and yourself. Just use the C locale and settings
# for the compilation. They can still be overriden by make LANG=<whatever>
# but that is general a not very good idea
include $(top_builddir)/version.mk

LANG = C
LC_ALL = C

libdir = $(abs_top_srcdir)/lib

AM_CPPFLAGS = -D_POSIX_C_SOURCE=200112L -D_XOPEN_SOURCE=600 -D_BSD_SOURCE
AM_CPPFLAGS += -DTEST -I"$(libdir)" -I"$(abs_top_builddir)/lib"

EXTRA_DIST =
EXTRA_DIST += $(dt_tests)
EXTRA_DIST += $(batch_tests)
EXTRA_DIST += $(BUILT_SOURCES)
TESTS = $(bin_tests) $(dt_tests) $(batch_tests)
TESTS_ENVIRONMENT =
TEST_EXTENSIONS =
BUILT_SOURCES =
dt_tests =
bin_tests =
batch_tests =
check_PROGRAMS =
CLEANFILES = $(check_PROGRAMS)
SUFFIXES =

TEST_EXTENSIONS += .clit
TESTS_ENVIRONMENT += root=$(top_srcdir)
CLIT_LOG_COMPILER = $(builddir)/clittool
AM_CLIT_LOG_FLAGS = -v --builddir "$(top_builddir)/src" --timeout 20

TESTS_ENVIRONMENT += GPERF=$(GPERF)
TESTS_ENVIRONMENT += GDATE=$(GDATE)
TESTS_ENVIRONMENT += have_gdate="$(have_gdate)"

dt_tests += dseq.01.clit
dt_tests += dseq.02.clit
dt_tests += dseq.03.clit
dt_tests += dseq.04.clit
dt_tests += dseq.05.clit
dt_tests += dseq.06.clit
dt_tests += dseq.07.clit
dt_tests += dseq.08.clit
dt_tests += dseq.09.clit
dt_tests += dseq.10.clit
dt_tests += dseq.11.clit
dt_tests += dseq.12.clit
dt_tests += dseq.13.clit
dt_tests += dseq.14.clit
dt_tests += dseq.15.clit
dt_tests += dseq.16.clit
dt_tests += dseq.17.clit
dt_tests += dseq.18.clit
dt_tests += dseq.19.clit
dt_tests += dseq.20.clit
dt_tests += dseq.21.clit
dt_tests += dseq.22.clit
dt_tests += dseq.23.clit
dt_tests += dseq.24.clit

dt_tests += dconv.001.clit
dt_tests += dconv.002.clit
dt_tests += dconv.003.clit
dt_tests += dconv.004.clit
dt_tests += dconv.005.clit
dt_tests += dconv.006.clit
dt_tests += dconv.007.clit
dt_tests += dconv.008.clit
dt_tests += dconv.009.clit
dt_tests += dconv.010.clit
dt_tests += dconv.011.clit
dt_tests += dconv.012.clit
dt_tests += dconv.013.clit
dt_tests += dconv.014.clit
dt_tests += dconv.015.clit
dt_tests += dconv.016.clit
dt_tests += dconv.017.clit
dt_tests += dconv.018.clit
dt_tests += dconv.019.clit
dt_tests += dconv.020.clit
dt_tests += dconv.021.clit
dt_tests += dconv.022.clit
dt_tests += dconv.023.clit
dt_tests += dconv.024.clit
dt_tests += dconv.025.clit
dt_tests += dconv.026.clit
dt_tests += dconv.027.clit
dt_tests += dconv.028.clit
dt_tests += dconv.029.clit
dt_tests += dconv.030.clit
dt_tests += dconv.031.clit
dt_tests += dconv.032.clit
dt_tests += dconv.033.clit
dt_tests += dconv.034.clit
dt_tests += dconv.035.clit
dt_tests += dconv.036.clit
dt_tests += dconv.037.clit
dt_tests += dconv.038.clit
dt_tests += dconv.039.clit
dt_tests += dconv.040.clit
dt_tests += dconv.041.clit
dt_tests += dconv.042.clit
dt_tests += dconv.043.clit
dt_tests += dconv.044.clit
dt_tests += dconv.045.clit
dt_tests += dconv.046.clit
dt_tests += dconv.047.clit
dt_tests += dconv.048.clit
dt_tests += dconv.049.clit
dt_tests += dconv.050.clit
dt_tests += dconv.051.clit
dt_tests += dconv.052.clit
dt_tests += dconv.053.clit
dt_tests += dconv.054.clit
dt_tests += dconv.055.clit
dt_tests += dconv.056.clit
dt_tests += dconv.057.clit
dt_tests += dconv.058.clit
dt_tests += dconv.059.clit
dt_tests += dconv.060.clit
dt_tests += dconv.061.clit
dt_tests += dconv.062.clit
dt_tests += dconv.063.clit
dt_tests += dconv.064.clit
dt_tests += dconv.065.clit
dt_tests += dconv.066.clit
dt_tests += dconv.067.clit
dt_tests += dconv.068.clit
dt_tests += dconv.069.clit
dt_tests += dconv.070.clit
dt_tests += dconv.071.clit
dt_tests += dconv.072.clit
dt_tests += dconv.073.clit
dt_tests += dconv.074.clit
dt_tests += dconv.075.clit
dt_tests += dconv.076.clit
dt_tests += dconv.077.clit
dt_tests += dconv.078.clit
dt_tests += dconv.079.clit
dt_tests += dconv.080.clit
dt_tests += dconv.081.clit
dt_tests += dconv.082.clit
dt_tests += dconv.083.clit
dt_tests += dconv.084.clit
dt_tests += dconv.085.clit
dt_tests += dconv.086.clit
dt_tests += dconv.087.clit
dt_tests += dconv.088.clit
dt_tests += dconv.089.clit
dt_tests += dconv.090.clit
dt_tests += dconv.091.clit
dt_tests += dconv.092.clit
dt_tests += dconv.093.clit
dt_tests += dconv.094.clit
dt_tests += dconv.095.clit
dt_tests += dconv.096.clit
dt_tests += dconv.097.clit
dt_tests += dconv.098.clit
dt_tests += dconv.099.clit
dt_tests += dconv.100.clit
dt_tests += dconv.101.clit
dt_tests += dconv.102.clit

dt_tests += dadd.001.clit
dt_tests += dadd.002.clit
dt_tests += dadd.003.clit
dt_tests += dadd.004.clit
dt_tests += dadd.005.clit
dt_tests += dadd.006.clit
dt_tests += dadd.007.clit
dt_tests += dadd.008.clit
dt_tests += dadd.009.clit
dt_tests += dadd.010.clit
dt_tests += dadd.011.clit
dt_tests += dadd.012.clit
dt_tests += dadd.013.clit
dt_tests += dadd.014.clit
dt_tests += dadd.015.clit
dt_tests += dadd.016.clit
dt_tests += dadd.017.clit
dt_tests += dadd.018.clit
dt_tests += dadd.019.clit
dt_tests += dadd.020.clit
dt_tests += dadd.021.clit
dt_tests += dadd.022.clit
dt_tests += dadd.023.clit
dt_tests += dadd.024.clit
dt_tests += dadd.025.clit
dt_tests += dadd.026.clit
dt_tests += dadd.027.clit
dt_tests += dadd.028.clit
dt_tests += dadd.029.clit
dt_tests += dadd.030.clit
dt_tests += dadd.031.clit
dt_tests += dadd.032.clit
dt_tests += dadd.033.clit
dt_tests += dadd.034.clit
dt_tests += dadd.035.clit
dt_tests += dadd.036.clit
dt_tests += dadd.037.clit
dt_tests += dadd.038.clit
dt_tests += dadd.039.clit
dt_tests += dadd.040.clit
dt_tests += dadd.041.clit
dt_tests += dadd.042.clit
dt_tests += dadd.043.clit
dt_tests += dadd.044.clit
dt_tests += dadd.045.clit
dt_tests += dadd.046.clit
dt_tests += dadd.047.clit
dt_tests += dadd.048.clit
dt_tests += dadd.049.clit
dt_tests += dadd.050.clit
dt_tests += dadd.051.clit
dt_tests += dadd.052.clit
dt_tests += dadd.053.clit
dt_tests += dadd.054.clit
dt_tests += dadd.055.clit
dt_tests += dadd.056.clit
dt_tests += dadd.057.clit
dt_tests += dadd.058.clit
dt_tests += dadd.059.clit
dt_tests += dadd.060.clit
dt_tests += dadd.061.clit
dt_tests += dadd.062.clit
dt_tests += dadd.063.clit
dt_tests += dadd.064.clit
dt_tests += dadd.065.clit
dt_tests += dadd.066.clit
dt_tests += dadd.067.clit
dt_tests += dadd.068.clit
dt_tests += dadd.069.clit
dt_tests += dadd.070.clit
dt_tests += dadd.071.clit
dt_tests += dadd.072.clit
dt_tests += dadd.073.clit
dt_tests += dadd.074.clit
dt_tests += dadd.075.clit
dt_tests += dadd.076.clit
dt_tests += dadd.077.clit
dt_tests += dadd.078.clit
dt_tests += dadd.079.clit
dt_tests += dadd.080.clit
dt_tests += dadd.081.clit
dt_tests += dadd.082.clit
dt_tests += dadd.083.clit
dt_tests += dadd.084.clit
dt_tests += dadd.085.clit
dt_tests += dadd.086.clit

dt_tests += dtest.001.clit
dt_tests += dtest.002.clit
dt_tests += dtest.003.clit
dt_tests += dtest.004.clit
dt_tests += dtest.005.clit
dt_tests += dtest.006.clit
dt_tests += dtest.007.clit
dt_tests += dtest.008.clit
dt_tests += dtest.009.clit

dt_tests += ddiff.001.clit
dt_tests += ddiff.002.clit
dt_tests += ddiff.003.clit
dt_tests += ddiff.004.clit
dt_tests += ddiff.005.clit
dt_tests += ddiff.006.clit
dt_tests += ddiff.007.clit
dt_tests += ddiff.008.clit
dt_tests += ddiff.009.clit
dt_tests += ddiff.010.clit
dt_tests += ddiff.011.clit
dt_tests += ddiff.012.clit
dt_tests += ddiff.013.clit
dt_tests += ddiff.014.clit
dt_tests += ddiff.015.clit
dt_tests += ddiff.016.clit
dt_tests += ddiff.017.clit
dt_tests += ddiff.018.clit
dt_tests += ddiff.019.clit
dt_tests += ddiff.020.clit
dt_tests += ddiff.021.clit
dt_tests += ddiff.022.clit
dt_tests += ddiff.023.clit
dt_tests += ddiff.024.clit
dt_tests += ddiff.025.clit
dt_tests += ddiff.026.clit
dt_tests += ddiff.027.clit
dt_tests += ddiff.028.clit
dt_tests += ddiff.029.clit
dt_tests += ddiff.030.clit
dt_tests += ddiff.031.clit
dt_tests += ddiff.032.clit
dt_tests += ddiff.033.clit
dt_tests += ddiff.034.clit
dt_tests += ddiff.035.clit
dt_tests += ddiff.036.clit
dt_tests += ddiff.037.clit
dt_tests += ddiff.038.clit
dt_tests += ddiff.039.clit
dt_tests += ddiff.040.clit
dt_tests += ddiff.041.clit
dt_tests += ddiff.042.clit
dt_tests += ddiff.043.clit
dt_tests += ddiff.044.clit
dt_tests += ddiff.045.clit
dt_tests += ddiff.046.clit
dt_tests += ddiff.047.clit
dt_tests += ddiff.048.clit
dt_tests += ddiff.049.clit
dt_tests += ddiff.050.clit
dt_tests += ddiff.051.clit
dt_tests += ddiff.052.clit
dt_tests += ddiff.053.clit
dt_tests += ddiff.054.clit
dt_tests += ddiff.055.clit
dt_tests += ddiff.056.clit
dt_tests += ddiff.057.clit
dt_tests += ddiff.058.clit
dt_tests += ddiff.059.clit
dt_tests += ddiff.060.clit
dt_tests += ddiff.061.clit
dt_tests += ddiff.062.clit

dt_tests += dgrep.001.clit
dt_tests += dgrep.002.clit
dt_tests += dgrep.003.clit
dt_tests += dgrep.004.clit
dt_tests += dgrep.005.clit
dt_tests += dgrep.006.clit
dt_tests += dgrep.007.clit
dt_tests += dgrep.008.clit
dt_tests += dgrep.009.clit
dt_tests += dgrep.010.clit
dt_tests += dgrep.011.clit
dt_tests += dgrep.012.clit
dt_tests += dgrep.013.clit
dt_tests += dgrep.014.clit
dt_tests += dgrep.015.clit
dt_tests += dgrep.016.clit
dt_tests += dgrep.017.clit
dt_tests += dgrep.018.clit
dt_tests += dgrep.019.clit
dt_tests += dgrep.020.clit
dt_tests += dgrep.021.clit
dt_tests += dgrep.022.clit
dt_tests += dgrep.023.clit
dt_tests += dgrep.024.clit
dt_tests += dgrep.025.clit
dt_tests += dgrep.026.clit
dt_tests += dgrep.027.clit
dt_tests += dgrep.028.clit
dt_tests += dgrep.029.clit
dt_tests += dgrep.030.clit
dt_tests += dgrep.031.clit
dt_tests += dgrep.032.clit
dt_tests += dgrep.033.clit
dt_tests += dgrep.034.clit
dt_tests += dgrep.035.clit
dt_tests += dgrep.036.clit
dt_tests += dgrep.037.clit
dt_tests += dgrep.038.clit
dt_tests += dgrep.039.clit
dt_tests += dgrep.040.clit

dt_tests += dround.001.clit
dt_tests += dround.002.clit
dt_tests += dround.003.clit
dt_tests += dround.004.clit
dt_tests += dround.005.clit
dt_tests += dround.006.clit
dt_tests += dround.007.clit
dt_tests += dround.008.clit
dt_tests += dround.009.clit
dt_tests += dround.010.clit
dt_tests += dround.011.clit
dt_tests += dround.012.clit
dt_tests += dround.013.clit
dt_tests += dround.014.clit
dt_tests += dround.015.clit
dt_tests += dround.016.clit
dt_tests += dround.017.clit
dt_tests += dround.018.clit
dt_tests += dround.019.clit
dt_tests += dround.020.clit
dt_tests += dround.021.clit
dt_tests += dround.022.clit
dt_tests += dround.023.clit
dt_tests += dround.024.clit


dt_tests += tseq.01.clit
dt_tests += tseq.02.clit
dt_tests += tseq.03.clit
dt_tests += tseq.04.clit
dt_tests += tseq.05.clit
dt_tests += tseq.06.clit
dt_tests += tseq.07.clit
dt_tests += tseq.08.clit
dt_tests += tseq.09.clit
dt_tests += tseq.10.clit
dt_tests += tseq.11.clit
dt_tests += tseq.12.clit
dt_tests += tseq.13.clit
dt_tests += tseq.14.clit
dt_tests += tseq.15.clit
dt_tests += tseq.16.clit
dt_tests += tseq.17.clit
dt_tests += tseq.18.clit
dt_tests += tseq.19.clit

dt_tests += tdiff.001.clit
dt_tests += tdiff.002.clit
dt_tests += tdiff.003.clit
dt_tests += tdiff.004.clit
dt_tests += tdiff.005.clit
dt_tests += tdiff.006.clit
dt_tests += tdiff.007.clit
dt_tests += tdiff.008.clit
dt_tests += tdiff.009.clit
dt_tests += tdiff.010.clit
dt_tests += tdiff.011.clit
dt_tests += tdiff.012.clit
dt_tests += tdiff.013.clit

dt_tests += tadd.001.clit
dt_tests += tadd.002.clit
dt_tests += tadd.003.clit
dt_tests += tadd.004.clit
dt_tests += tadd.005.clit
dt_tests += tadd.006.clit
dt_tests += tadd.007.clit
dt_tests += tadd.008.clit
dt_tests += tadd.009.clit
dt_tests += tadd.010.clit

dt_tests += tgrep.001.clit
dt_tests += tgrep.002.clit
dt_tests += tgrep.003.clit

dt_tests += ttest.001.clit
dt_tests += ttest.002.clit
dt_tests += ttest.003.clit
dt_tests += ttest.004.clit
dt_tests += ttest.005.clit
dt_tests += ttest.006.clit
dt_tests += ttest.007.clit

dt_tests += tconv.001.clit
dt_tests += tconv.002.clit
dt_tests += tconv.003.clit
dt_tests += tconv.004.clit
dt_tests += tconv.005.clit
dt_tests += tconv.006.clit

dt_tests += tround.001.clit
dt_tests += tround.002.clit
dt_tests += tround.003.clit
dt_tests += tround.004.clit


dt_tests += dtconv.001.clit
dt_tests += dtconv.002.clit
dt_tests += dtconv.003.clit
dt_tests += dtconv.004.clit
dt_tests += dtconv.005.clit
dt_tests += dtconv.006.clit
dt_tests += dtconv.007.clit
dt_tests += dtconv.008.clit
dt_tests += dtconv.009.clit
dt_tests += dtconv.010.clit
dt_tests += dtconv.011.clit
dt_tests += dtconv.012.clit
dt_tests += dtconv.013.clit
dt_tests += dtconv.014.clit
dt_tests += dtconv.015.clit
dt_tests += dtconv.016.clit
dt_tests += dtconv.017.clit
dt_tests += dtconv.018.clit
dt_tests += dtconv.019.clit
dt_tests += dtconv.020.clit
dt_tests += dtconv.021.clit
dt_tests += dtconv.022.clit
dt_tests += dtconv.023.clit
if ZONEINFO_UTC_RIGHT
dt_tests += dtconv.024.clit
dt_tests += dtconv.025.clit
dt_tests += dtconv.026.clit
dt_tests += dtconv.027.clit
dt_tests += dtconv.028.clit
dt_tests += dtconv.029.clit
dt_tests += dtconv.030.clit
dt_tests += dtconv.031.clit
dt_tests += dtconv.032.clit
dt_tests += dtconv.033.clit
endif  ZONEINFO_UTC_RIGHT
dt_tests += dtconv.034.clit
dt_tests += dtconv.035.clit
dt_tests += dtconv.036.clit
dt_tests += dtconv.037.clit
dt_tests += dtconv.038.clit
dt_tests += dtconv.039.clit
dt_tests += dtconv.040.clit
dt_tests += dtconv.041.clit
dt_tests += dtconv.042.clit
dt_tests += dtconv.043.clit
dt_tests += dtconv.044.clit
dt_tests += dtconv.045.clit
dt_tests += dtconv.046.clit
dt_tests += dtconv.047.clit
dt_tests += dtconv.048.clit

dt_tests += convt.ymcw-ymd.clit
dt_tests += convt.ymcw-ywd.clit
dt_tests += convt.ymd-ymcw.clit
dt_tests += convt.ymd-ywd.clit
dt_tests += convt.ywd-ymcw.clit
dt_tests += convt.ywd-ymd.clit

dt_tests += dtseq.01.clit
dt_tests += dtseq.02.clit

dt_tests += dtadd.001.clit
dt_tests += dtadd.002.clit
dt_tests += dtadd.003.clit
dt_tests += dtadd.004.clit
dt_tests += dtadd.005.clit
dt_tests += dtadd.006.clit
dt_tests += dtadd.007.clit
dt_tests += dtadd.008.clit
dt_tests += dtadd.009.clit
dt_tests += dtadd.010.clit
dt_tests += dtadd.011.clit
dt_tests += dtadd.012.clit
dt_tests += dtadd.013.clit
dt_tests += dtadd.014.clit
dt_tests += dtadd.015.clit
dt_tests += dtadd.016.clit
dt_tests += dtadd.017.clit
dt_tests += dtadd.018.clit
dt_tests += dtadd.019.clit
dt_tests += dtadd.020.clit
dt_tests += dtadd.021.clit
dt_tests += dtadd.022.clit
dt_tests += dtadd.023.clit
dt_tests += dtadd.024.clit
dt_tests += dtadd.025.clit
dt_tests += dtadd.026.clit
dt_tests += dtadd.027.clit
dt_tests += dtadd.028.clit
dt_tests += dtadd.029.clit
if WITH_LEAP_SECONDS
dt_tests += dtadd.030.clit
dt_tests += dtadd.031.clit
endif  ## WITH_LEAP_SECONDS
dt_tests += dtadd.032.clit
dt_tests += dtadd.033.clit
if WITH_LEAP_SECONDS
dt_tests += dtadd.034.clit
dt_tests += dtadd.035.clit
endif  ## WITH_LEAP_SECONDS
dt_tests += dtadd.036.clit
dt_tests += dtadd.037.clit
dt_tests += dtadd.038.clit
dt_tests += dtadd.039.clit
dt_tests += dtadd.040.clit
## multi-sed
dt_tests += dtadd.041.clit
dt_tests += dtadd.042.clit

dt_tests += dtgrep.001.clit
dt_tests += dtgrep.002.clit
dt_tests += dtgrep.003.clit
dt_tests += dtgrep.004.clit
dt_tests += dtgrep.005.clit
dt_tests += dtgrep.006.clit
dt_tests += dtgrep.007.clit
dt_tests += dtgrep.008.clit
dt_tests += dtgrep.009.clit
dt_tests += dtgrep.010.clit
dt_tests += dtgrep.011.clit
dt_tests += dtgrep.012.clit

dt_tests += dttest.001.clit
dt_tests += dttest.002.clit
dt_tests += dttest.003.clit
dt_tests += dttest.004.clit
dt_tests += dttest.005.clit
dt_tests += dttest.006.clit
dt_tests += dttest.007.clit
dt_tests += dttest.008.clit
dt_tests += dttest.009.clit
dt_tests += dttest.010.clit

dt_tests += dtdiff.001.clit
dt_tests += dtdiff.002.clit
dt_tests += dtdiff.003.clit
dt_tests += dtdiff.004.clit
dt_tests += dtdiff.005.clit
dt_tests += dtdiff.006.clit
dt_tests += dtdiff.007.clit
dt_tests += dtdiff.008.clit
dt_tests += dtdiff.009.clit
dt_tests += dtdiff.010.clit
dt_tests += dtdiff.011.clit
dt_tests += dtdiff.012.clit
dt_tests += dtdiff.013.clit
dt_tests += dtdiff.014.clit
dt_tests += dtdiff.015.clit
dt_tests += dtdiff.016.clit
dt_tests += dtdiff.017.clit
dt_tests += dtdiff.018.clit
if WITH_LEAP_SECONDS
dt_tests += dtdiff.019.clit
dt_tests += dtdiff.020.clit
dt_tests += dtdiff.021.clit
dt_tests += dtdiff.022.clit
endif  ## WITH_LEAP_SECONDS
dt_tests += dtdiff.023.clit
dt_tests += dtdiff.024.clit
dt_tests += dtdiff.025.clit
dt_tests += dtdiff.026.clit
dt_tests += dtdiff.027.clit
dt_tests += dtdiff.028.clit
dt_tests += dtdiff.029.clit
dt_tests += dtdiff.030.clit
dt_tests += dtdiff.031.clit
dt_tests += dtdiff.032.clit
dt_tests += dtdiff.033.clit
dt_tests += dtdiff.034.clit
dt_tests += dtdiff.035.clit
dt_tests += dtdiff.036.clit
dt_tests += dtdiff.037.clit
dt_tests += dtdiff.038.clit
dt_tests += dtdiff.039.clit
dt_tests += dtdiff.040.clit

dt_tests += dtround.001.clit
dt_tests += dtround.002.clit
dt_tests += dtround.003.clit
dt_tests += dtround.004.clit
dt_tests += dtround.005.clit
dt_tests += dtround.006.clit
dt_tests += dtround.007.clit
dt_tests += dtround.008.clit
dt_tests += dtround.009.clit
dt_tests += dtround.010.clit
dt_tests += dtround.011.clit
dt_tests += dtround.012.clit
dt_tests += dtround.013.clit
dt_tests += dtround.014.clit

dt_tests += strptime.001.clit
dt_tests += strptime.002.clit

## we should check if the zones in these tests actually exist
## also failing tests here should be soft-fails because that could
## easily be an outdated zoneinfo file
dt_tests += dtz.001.clit
dt_tests += dtz.002.clit

check_PROGRAMS += struct-1
check_PROGRAMS += struct-2
check_PROGRAMS += struct-3
check_PROGRAMS += struct-4
check_PROGRAMS += struct-5
check_PROGRAMS += struct-6
check_PROGRAMS += struct-7
check_PROGRAMS += struct-8
check_PROGRAMS += struct-9
check_PROGRAMS += enum-1
check_PROGRAMS += dtcore-strp
check_PROGRAMS += dtcore-conv
check_PROGRAMS += dtcore-add
check_PROGRAMS += time-core-add
check_PROGRAMS += basic_ymd_get_wday
check_PROGRAMS += basic_get_jan01_wday
check_PROGRAMS += basic_md_get_yday
check_PROGRAMS += basic_get_dom_wday

bin_tests += struct-1
bin_tests += struct-2
bin_tests += struct-3
bin_tests += struct-4
bin_tests += struct-5
bin_tests += struct-6
bin_tests += struct-7
bin_tests += struct-8
bin_tests += struct-9
bin_tests += enum-1
bin_tests += dtcore-strp
bin_tests += dtcore-conv
bin_tests += dtcore-add
bin_tests += time-core-add
bin_tests += basic_ymd_get_wday
bin_tests += basic_get_jan01_wday
bin_tests += basic_get_dom_wday
bin_tests += basic_md_get_yday

## batch checks
batch_tests += dseq-cnt.1.sh
if HAVE_GDATE
TESTS_ENVIRONMENT += have_gdate_2039="$(have_gdate_2039)"
batch_tests += dseq-cnt.2.sh
batch_tests += dseq-cnt.3.sh
batch_tests += dconv-batch.1.sh
batch_tests += dconv-batch.2.sh
endif  HAVE_GDATE


check_PROGRAMS += clittool
clittool_CPPFLAGS = $(AM_CPPFLAGS)
clittool_CPPFLAGS += -D_GNU_SOURCE
EXTRA_DIST += clittool.ggo
BUILT_SOURCES += clittool.x clittool.xh


## ggo rule
SUFFIXES += .ggo
SUFFIXES += .x
.ggo.x:
	$(AM_V_GEN) gengetopt -F $* -G -c x -H xh -i $<
	@sed -e 's,config.h,version.h,g' \
	     -e 's,_PARSER_VERSION VERSION,_PARSER_VERSION "$(VERSION)",g' \
	     $@h > $@h-t \
	&& mv $@h-t $@h
SUFFIXES += .xh
.ggo.xh:
	touch $@

clean-local:
	-rm -rf *.tmpd

## Makefile.am ends here
