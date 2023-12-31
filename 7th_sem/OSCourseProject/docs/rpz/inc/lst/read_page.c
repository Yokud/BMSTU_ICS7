static asmlinkage int (*orig_bdev_read_page)(struct block_device *bdev, sector_t sector, 
struct page *page);

static asmlinkage int hook_bdev_read_page(struct block_device *bdev, sector_t sector, 
	struct page *page)
{
    int res;

    res = orig_bdev_read_page(bdev, sector, page);
    pr_info("read page: from /dev/sda");

    return res;
}