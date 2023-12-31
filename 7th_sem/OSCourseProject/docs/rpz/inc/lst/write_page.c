static asmlinkage int (*orig_bdev_write_page)(struct block_device *bdev, sector_t sector, 
struct page *page, struct writeback_control **wc);

static asmlinkage int hook_bdev_write_page(struct block_device *bdev, sector_t sector, 
struct page *page, struct writeback_control **wc)
{
    int res;

    res = orig_bdev_write_page(bdev, sector, page, wc);
    pr_info("write page: to /dev/sda");

    return res;
}
