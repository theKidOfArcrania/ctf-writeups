from subprocess import check_output
strs = ['dqzkenxmpsdoe_qkihmd', 'jffglzbo_zghqpnqqfjs', 'kdwx_vl_rnesamuxugap',
        'ozntzohegxagreedxukr', 'xujaowgbjjhydjmmtapo', 'pwbzgymqvpmznoanomzx',
        'qaqhrjofhfiuyt_okwxn', 'a_anqkczwbydtdwwbjwi', 'zoljafyuxinnvkxsskdu',
        'irdlddjjokwtpbrrr_yj', 'cecckcvaltzejskg_qrc', 'vlpwstrhtcpxxnbbcbhv',
        'spirysagnyujbqfhldsk', 'bcyqbikpuhlwordznpth', '_xkiiusddvvicipuzyna',
        'wsxyupdsqatrkzgawzbt', 'ybg_wmftbdcvlhhidril', 'ryvmngilaqkbsyojgify',
        'mvefjqtxzmxf_vcyhelf', 'hjhofxwrk_rpwli_mxv_', 'enupmannieqqzcyevs_w',
        'uhmvvb_cfgjkggjpavub', 'gktdphqiswomuwzvjtog', 'lgoehepwclbaifvtfoeq',
        'nm_uxrukmof_fxsfpcqz', 'ttsbclzyyuslmutcylcm']


def diff(a, b):
    return int(check_output(['./test', a, b]))

def sumdiff(a):
    ret = 0
    for x in strs:
        ret += diff(x, a)
    return ret

#    assert len(a) == len(b)
#    return sum(x != y for x, y in zip(a, b))

# Make sure all strings going down are unique
#buckets = [set() for i in range(20)]
#for s in strs:
#    for i in range(20):
#        if s[i] in buckets[i]:
#            print((s, s[i]))
#        buckets[i].add(s[i])
#

res = ['*' for i in range(20)]
for i in range(15):
    res[i] = strs[i][i]
    x = ''.join(res)
    print('%s, %d' % (x, sumdiff(x)))


res += '*****'
print(res)
        

